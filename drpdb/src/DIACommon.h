#pragma once
#include "windows.h"
#include "dia2.h"
#include "cvconst.h"
#include "diacreate.h"
#include <comdef.h>
#include <atlcomcli.h>
#include <string>
#include <algorithm>

std::string getOption(const char* name);

namespace DIA2
{
	struct Provider
	{
		CComPtr<IDiaDataSource> source;
		CComPtr<IDiaSession> session;

		Provider();
		bool load(const char* inFile);
	};

	template<class T, class Enumerate, class Predicate>
	void ReadTable(Enumerate enumerator, Predicate p, const char* name)
	{
		LONG num = 0;
		enumerator->get_Count(&num);
		if (num < 0) {
			return;
		}

		p.init(num);
		std::cout << "Reading " << num << " " << name << std::endl;

		const ULONG ChunkSize = 4096;
		ULONG totalNumFetched{ 0 };
		while(totalNumFetched < (ULONG)num)
		{
			const ULONG numToFetch = std::min( num - totalNumFetched, ChunkSize );
			auto fetched = std::make_unique<CComPtr<T>[]>( numToFetch );
			ULONG numFetched = 0;
			const auto HR = enumerator->Next( numToFetch, (T**)fetched.get(), &numFetched );
			if (FAILED( HR ) || numFetched == 0)
				break;
			for (ULONG f = 0; f < numFetched; ++f)
			{
				p.element( fetched[f] );
			}
			totalNumFetched += numFetched;
		}
	}
	template<class PSectionContrib, class PInjSrc, class PSrcFiles, class PSymbols, class PSegMap, class PInputAsms, class P_Frame, class P_Lines>
	void ReadTables(IDiaSession* session, PSectionContrib f_contrib, PInjSrc f_inj, PSrcFiles f_src,  PSymbols f_syms, PSegMap f_segmap, PInputAsms f_inasm, P_Frame f_frame, P_Lines f_lines)
	{
		CComPtr<IDiaEnumTables> streamEnum = nullptr;
		session->getEnumTables(&streamEnum);
		while (streamEnum)
		{
			ULONG numFetched = 0;
			CComPtr<IDiaTable> table = nullptr;
			streamEnum->Next(1, &table, &numFetched);
			if (table == nullptr || numFetched < 1)
				break;
			CComBSTR enumDataName;
			table->get_name(&enumDataName);
			if (wcscmp(enumDataName, DiaTable_Sections) == 0)
			{
				CComPtr<IDiaEnumSectionContribs> pEnumSec = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumSectionContribs), (void**)&pEnumSec))
				{
					DIA2::ReadTable<IDiaSectionContrib>(pEnumSec, f_contrib, "sections");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_InjSrc) == 0)
			{
				CComPtr<IDiaEnumInjectedSources> pEnumInjected = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumInjectedSources), (void**)&pEnumInjected))
				{
					DIA2::ReadTable<IDiaInjectedSource>(pEnumInjected, f_inj, "injected sources");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_SrcFiles) == 0)
			{
				CComPtr<IDiaEnumSourceFiles> pEnumSrc = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumSourceFiles), (void**)&pEnumSrc))
				{
					DIA2::ReadTable<IDiaSourceFile>(pEnumSrc, f_src, "source files");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_Symbols) == 0)
			{
				CComPtr<IDiaEnumSymbols> pEnumSym = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumSymbols), (void**)&pEnumSym))
				{
					DIA2::ReadTable<IDiaSymbol>(pEnumSym, f_syms, "symbols");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_SegMap) == 0)
			{
				CComPtr<IDiaEnumSegments> pEnumSeg = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumSegments), (void**)&pEnumSeg))
				{
					DIA2::ReadTable<IDiaSegment>(pEnumSeg, f_segmap, "segment map");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_InputAssemblyFiles) == 0)
			{
				CComPtr<IDiaEnumInputAssemblyFiles> pEnumAsm = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumInputAssemblyFiles), (void**)&pEnumAsm))
				{
					DIA2::ReadTable<IDiaInputAssemblyFile>(pEnumAsm, f_inasm, "input assemblies");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_FrameData) == 0)
			{
				CComPtr<IDiaEnumFrameData> pEnumFrame = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumFrameData), (void**)&pEnumFrame))
				{
					DIA2::ReadTable<IDiaFrameData>(pEnumFrame, f_frame, "frame data");
				}
			}
			else if (wcscmp(enumDataName, DiaTable_LineNums) == 0)
			{
				CComPtr<IDiaEnumLineNumbers> pEnumLineNums = nullptr;
				if (S_OK == table->QueryInterface(__uuidof(IDiaEnumLineNumbers), (void**)&pEnumLineNums))
				{
					DIA2::ReadTable<IDiaLineNumber>(pEnumLineNums, f_lines, "line numbers");
				}
			}
		}
	}
}
