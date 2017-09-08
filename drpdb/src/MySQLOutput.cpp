#include <windows.h>
#include "mysql.h"

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "drpdb.h"
#include "CSVWriter.h"
#include "SQLSchemaWriter.h"

namespace
{
	struct SingleConnection
	{
		MYSQL* mysql;
		SingleConnection(const char* host, const char* user, const char* pass, const char* db, int port)
		{
			mysql = mysql_init(nullptr);
			if (mysql)
			{
				my_bool auto_reconnect = true;
				mysql_options(mysql, MYSQL_OPT_RECONNECT, &auto_reconnect);
				if (!mysql_real_connect(mysql, host, user, pass, db, port, nullptr, 0))
				{
					set_error(mysql_error(mysql));
				}
			}
			else
			{
				set_error("Failed to initialize mysql");
			}
		}
		void execute(const char* begin, const char* end)
		{
			if (mysql)
			{
				if (mysql_real_query(mysql, begin, static_cast<unsigned long>(end - begin)) == 0)
				{
					if (mysql_warning_count(mysql) > 0)
					{
						int a = 2;
						++a;
					}
				}
				else
				{
					set_error(mysql_error(mysql));
				}
			}
		}
		~SingleConnection()
		{
			if (mysql)
				mysql_close(mysql);
		}
	};
	struct OutputData
	{
		SymbolData& Results;
		std::vector<std::string> UploadCommands;
		std::string tempdir_escaped;
		std::string tempdir;
		int port;
		std::string host;
		std::string user;
		std::string pass;
		std::string db;
		OutputData(SymbolData& Res)
			:Results(Res)
		{
		}
		void init()
		{
			host = getOption("-host");
			user = getOption("-user");
			pass = getOption("-pass");
			db = getOption("-db");


			if (host.empty() || user.empty() || db.empty())
			{
				throw "MySQL requires -host, -user, and -db settings.";
			}
			auto portstr = getOption("-port");
			if (portstr.empty())
			{
				port = 3306;
			}
			else
			{
				port = atoi(portstr.data());
				if (port == 0)
				{
					throw "Invalid -port specified.";
				}
			}

			tempdir = getOption("-tempdir");
			if (tempdir.size() == 0)
			{
				char buf[MAX_PATH + 1] = {};
				auto len = GetCurrentDirectoryA(MAX_PATH, buf);
				if (len > MAX_PATH)
					throw "tempdir path too long";
				tempdir = buf;
				tempdir += "\\temp\\";
			}
			CreateDirectoryA(tempdir.data(), nullptr);
			tempdir_escaped = replace(tempdir, "\\", "\\\\") + "\\\\";

			GenerateCommands();
		}
		void LoadTable(const std::string& name, const std::string& end)
		{
			std::string Cmd = "load data local infile '";
			Cmd += tempdir_escaped;
			Cmd += name;
			Cmd += "_values.txt' into table ";
			Cmd += name;
			Cmd += " fields terminated by ',' optionally enclosed by '\"' lines terminated by '\\n'";
			Cmd += end;
			Cmd += ";";

			UploadCommands.push_back(Cmd);
		}
		template<class T>
		void CreateTable(std::string tablename, std::string& EndClause, const char* desc)
		{
			T Value;
			UploadCommands.push_back(std::string("DROP TABLE IF EXISTS ") + tablename + ";");
			SQL::schema_writer Ar(true);

			Ar.Result += "CREATE TABLE ";
			Ar.Result += tablename.c_str();
			Ar.Result += "(";
			Ar << Value;
			Ar.Result += Ar.Keys;
			if (Ar.Result.back() == ',')
			{
				Ar.Result.pop_back();
			}
			Ar.Result += ") Engine=MyISAM";
			Ar.Result += " COMMENT='";
			std::string temp_desc = desc;
			temp_desc = replace(temp_desc, "'", "''");
			Ar.Result += temp_desc;
			Ar.Result += "';";
			UploadCommands.push_back(Ar.Result);

			Ar.LoadClause.pop_back();
			EndClause = Ar.LoadClause + ") " + Ar.SetClause;
		}


		template<class T>
		void PopulateTable(T TableBegin, T TableEnd, const std::string& name)
		{
			CSV::writer Ar(tempdir + name + "_values.txt", true, ',');
			while (TableBegin != TableEnd)
			{
				Ar << *TableBegin;
				Ar.backup();
				++TableBegin;
				Ar.out += "\n";
			}
			std::ofstream writer(Ar.outPath, std::ios::out | std::ios::binary);
			writer << Ar.out;
		}

		template<class T>
		void BuildTable(const std::vector<T>& Table, const std::string& name, const char* desc)
		{
			std::string EndClause;
			CreateTable<T>(name, EndClause, desc);
			PopulateTable(Table.begin(), Table.end(), name);
			LoadTable(name, EndClause);
		}

		template<class U, class T>
		void BuildTable(const std::unordered_map<U, T>& Table, const std::string& name, const char* desc)
		{
			std::string EndClause;
			CreateTable<T>(name, EndClause, desc);

			if (Results.Populate)
			{
				PopulateTable(Table.begin(), Table.end(), name);
			}
			LoadTable(name, EndClause);

		}

		void ParseProcedure(const std::string& sequence)
		{
			size_t prev = 0;
			auto next = sequence.find("#then_execute");
			std::string current;
			while (next != std::string::npos)
			{
				UploadCommands.emplace_back(sequence.substr(prev, next));
				prev = next + 14;
				next = sequence.find("#then_execute", prev);
			}
			UploadCommands.emplace_back(sequence.substr(prev));
		}
		void GenerateProcedures()
		{
			WIN32_FIND_DATAA found;
			auto search = FindFirstFileA("../../config/mysql/*.sql", &found);
			while (search != INVALID_HANDLE_VALUE)
			{
				std::ifstream file(std::string("../../config/mysql/") + found.cFileName);
				if (file.good())
				{
					std::string file_contents{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
					ParseProcedure(file_contents);
				}
				if (!FindNextFileA(search, &found))
				{
					break;
				}
			}
		}
		void GenerateCommands()
		{
			GenerateProcedures();
#define BEGIN_STRUCT(type, name, desc,category) BuildTable(Results.type, #name, desc );

#include "PDBReflection.inl"
		}
	};
	bool VerifyMysqlAvailable()
	{
	#ifdef WIN32
		static HANDLE library_handle = LoadLibrary( TEXT( "libmysql.dll" ) );
		if(library_handle == nullptr)
		{
			std::cerr << "Error: Mysql output not available 'Failed to load libmysql.dll'" << std::endl;
		}
		return library_handle != nullptr;
	#else
		return true;
	#endif
	}
}
namespace MySQL
{
	namespace
	{
		void output(SymbolData& Data)
		{
			OutputData Result(Data);
			Result.init();

			SingleConnection conn(Result.host.data(), Result.user.data(), Result.pass.data(), Result.db.data(), Result.port);

			int i = 0;
			while (!has_error() && i<Result.UploadCommands.size())
			{
				conn.execute(Result.UploadCommands[i].data(), Result.UploadCommands[i].data() + Result.UploadCommands[i].size());
				++i;
			}
		}

		static std::string describe()
		{
			return
				"    req: -host=<database server>\n    req: -user=<username>\n    req: -db=<database>\n    opt: -pass=<password>\n    opt: -port=<port number> (default 3306)\n    opt: -temp=<custom temp directory>";
		}
	}

	OutputEngine CreateEngine()
	{
		static const bool MysqlAvailable = VerifyMysqlAvailable( );
		OutputEngine res;
		if (MysqlAvailable) {
			res.name = "mysql";
			res.output = &output;
			res.describe = &describe;
		}
		return res;
	}
}
