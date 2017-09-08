#include "drpdb.h"
#include <iostream>
#include <chrono>
#include <windows.h>
#include <functional>
#include <algorithm>

static int gArgc;
static const char** gArgv;

std::string getOption(const char* name)
{
	for (int i = 0; i < gArgc; ++i)
	{
		if (auto found = strchr(gArgv[i], '='))
		{
			if (strncmp(gArgv[i], name, found - gArgv[i]) == 0)
			{
				if (*found + 1 == '\"')
				{
					auto found_end = strchr(found + 2, '\"');
					if (found_end == nullptr)
						return nullptr;
					return{ found + 1, found_end - 1 };
				}
				return found + 1;
			}
		}
	}
	return{};
}
bool getFlag(const char* name)
{
	for (int i = 0; i < gArgc; ++i)
	{
		if (strcmp(name, gArgv[i]) == 0)
		{
			return true;
		}
	}
	return false;
}

namespace DIA2
{
	void ReadSymbols(const char* File, SymbolData& Result);
	void Document();
}

std::function<void(SymbolData&)> get_input_engine()
{
	auto input = getOption("-in");
	if (input.size())
	{
		return [input](SymbolData& Syms) { DIA2::ReadSymbols(input.data(), Syms); };
	}
	return nullptr;
}

std::vector<OutputEngine> gEngines;

namespace ODBC { OutputEngine CreateEngine(); }
namespace MySQL { OutputEngine CreateEngine(); }
namespace CSV { OutputEngine CreateEngine(); }
namespace WikiDoc { void Output(const char* filename); }

void init_engines()
{
	gEngines.push_back(MySQL::CreateEngine());
	gEngines.push_back(CSV::CreateEngine());
	gEngines.push_back(ODBC::CreateEngine());
	// Remove null engines
	gEngines.erase( std::remove_if( begin( gEngines ), end( gEngines ), []( auto& e ) { return e.output == nullptr; } ), end( gEngines ) );

}

OutputEngine* get_output_engine()
{
	auto name = getOption("-out");
	if (!name.size())
	{
		return nullptr;
	}
	auto found = std::find_if(gEngines.begin(), gEngines.end(), [name](OutputEngine& e)
	{
		return e.name == name;
	});
	if (found == gEngines.end())
	{
		return nullptr;
	}
	return gEngines.data() + (found - gEngines.begin());
}

void PrintUsage()
{
	std::cout << std::endl;
	std::cout << "Options:\r\n";
	std::cout << "  -in=<filename>\r\n";
	std::cout << "      An absolute path pointing to an exe or pdb\r\n";
	std::cout << "      Writes empty schema if unspecified.\r\n";

	for (auto& e : gEngines)
	{
		std::cout << " -out=" << e.name << "\r\n";
		std::cout << e.describe() << "\r\n\r\n";
	}
	std::cout << " -doc\r\n";
	std::cout << "      Runs DIA API test suite, loading pdbs from config/doc/in.txt\r\n";
	std::cout << "      Results output into config/doc/out.txt\r\n\r\n";
	std::cout << " -wikidoc=<filename>\r\n";
	std::cout << "      Outputs markdown documentation at the given filename.\r\n";
	std::cout << "\r\n";
}
std::string gErr;
void set_error(const char* err)
{
	gErr += err;
	gErr += "\r\n";
}
bool has_error()
{
	return !gErr.empty();
}
int main(int argc, char** argv)
{
	gArgc = argc;
	gArgv = (const char**) argv;

	HMODULE hModule = GetModuleHandleA(NULL);
	CHAR path[MAX_PATH];
	GetModuleFileNameA(hModule, path, MAX_PATH);
	auto path_term = std::find(std::make_reverse_iterator(std::end(path)), std::make_reverse_iterator(path), '\\');
	if (path_term != std::make_reverse_iterator(std::end(path)))
	{
		*path_term = 0;
	}
	SetCurrentDirectoryA(path);

	if (getFlag("-doc"))
	{
		DIA2::Document();
		return 0;
	}
	auto wikidoc_filename = getOption("-wikidoc");
	if (wikidoc_filename.size() > 0)
	{
		WikiDoc::Output(wikidoc_filename.c_str());
		return 0;
	}

	init_engines();
	SymbolData S;
	std::string searchPath;

#if !defined(_DEBUG)
	_CrtSetDbgFlag( 0 );
#endif
	auto input = get_input_engine();
	auto output = get_output_engine();

	if (!output)
	{
		PrintUsage();
		return 1;
	}
	else
	{
		if (input)
		{
			input(S);
		}

		std::cout << "Saving results..." << std::endl;
		try
		{
			output->output(S);
		}
		catch (const char* ex)
		{
			set_error(ex);
		}

		if (!gErr.empty())
		{
			std::cerr << gErr;
			return 1;
		}
	}
}

