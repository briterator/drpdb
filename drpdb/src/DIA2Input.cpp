
#include "DIACommon.h"
#include <functional>
#include <iostream>
#include <windows.h>

#include "drpdb.h"
static bool no_addresses;
enum SymTagEnum;

Sym::BaseClass::BaseClass(IDiaSymbol* diaSymbol)  noexcept
{
	DWORD D;
	BOOL B;
	LONG Offset;
	access = Sym::Access::NONE;
	if (S_OK == diaSymbol->get_access(&D))
	{
		access = (Sym::Access)D;
	}

	diaSymbol->get_offset(&Offset);
	offset = Offset;

	diaSymbol->get_classParentId(&D);
	child_symbol = D;

	diaSymbol->get_virtualBaseClass(&B);
	virtual_ = !!B;

	diaSymbol->get_typeId(&D);
	parent_symbol = D;

	diaSymbol->get_virtualBaseDispIndex(&D);
	vdisp_index = D;

	diaSymbol->get_virtualBaseOffset(&D);
	vbase_offset = D;

	B = 0;
	diaSymbol->get_indirectVirtualBaseClass(&B);
	indirect_virtual = !!B;

	D = 0;
	vbase_type_symbol = 0;
	CComPtr<IDiaSymbol> vbase = nullptr;
	if (S_OK == diaSymbol->get_virtualBaseTableType(&vbase) && vbase)
	{
		if (S_OK == vbase->get_symIndexId(&D))
		{
			vbase_type_symbol = D;
		}
	}
}
Sym::Array::Array(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;

	DWORD D;
	diaSymbol->get_arrayIndexTypeId(&D);
	index_type_symbol = D;

	diaSymbol->get_count(&D);
	count = D;

	diaSymbol->get_rank(&D);
	rank = D;

	diaSymbol->get_typeId(&D);
	type_symbol = D;
}
template<class T>
void Sym::address_info::init(T* s)
{
	DWORD D = 0;
	if (no_addresses == false)
	{
		s->get_relativeVirtualAddress(&D);
	}
	rv = D;
}
Sym::SectionContrib::SectionContrib(IDiaSectionContrib* dia)  noexcept
{
	BOOL B = 0;
	DWORD D = 0;

	address.init(dia);

	dia->get_code(&B);
	code = !!B;

	dia->get_code16bit(&B);
	code_16bit = !!B;

	dia->get_comdat(&B);
	comdat = !!B;

	dia->get_compilandId(&D);
	compiland_symbol = D;

	dia->get_dataCrc(&D);
	data_crc = D;

	dia->get_discardable(&B);
	discardable = !!B;

	dia->get_execute(&B);
	executable = !!B;

	dia->get_initializedData(&B);
	initialized_data = !!B;

	dia->get_length(&D);
	length = !!D;

	dia->get_notCached(&B);
	cached = !B;

	dia->get_notPaged(&B);
	paged = !B;

	dia->get_read(&B);
	readable = !!B;

	dia->get_relocationsCrc(&D);
	relocations_crc = D;

	dia->get_remove(&B);
	remove = !!B;

	dia->get_share(&B);
	share = !!B;

	dia->get_uninitializedData(&B);
	uninitialized_data = !!B;

	dia->get_write(&B);
	writeable = !!B;
}
Sym::Block::Block(IDiaSymbol* dia, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	address.init(dia);
}
Sym::HeapAllocation::HeapAllocation(IDiaSymbol* dia, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;

	address.init(dia);
	DWORD D = 0;
	dia->get_typeId(&D);
	type_symbol = D;

}
Sym::Segment::Segment(IDiaSegment* segment)  noexcept
{
	BOOL B = 0;
	DWORD D = 0;
	ULONGLONG LL = 0;
	segment->get_addressSection(&D);
	address_section = D;

	segment->get_relativeVirtualAddress(&D);
	address_rv = D;

	segment->get_frame(&D);
	frame = D;

	segment->get_length(&D);
	length = D;

	segment->get_offset(&D);
	offset = D;

	segment->get_read(&B);
	readable = !!B;

	segment->get_write(&B);
	writable = !!B;

	segment->get_execute(&B);
	executable = !!B;
}
Sym::Inlined::Inlined(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	address.init(diaSymbol);
	DWORD D = 0;
	diaSymbol->get_PGOEdgeCount(&D);
	pgo_edges = D;

	D = 0;
	diaSymbol->get_typeId(&D);
	type_symbol = D;
}
Sym::Export::Export(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;

	DWORD D = 0;
	diaSymbol->get_relativeVirtualAddress(&D);
	address_offset = D;

	diaSymbol->get_rank(&D);
	rank = D;

	diaSymbol->get_ordinal(&D);
	ordinal = D;

	BOOL B = false;
	diaSymbol->get_constantExport(&B);
	const_export = !!B;

	diaSymbol->get_dataExport(&B);
	data_export = !!B;

	diaSymbol->get_privateExport(&B);
	private_export = !!B;

	diaSymbol->get_noNameExport(&B);
	noname = !!B;

	diaSymbol->get_exportHasExplicitlyAssignedOrdinal(&B);
	explicit_ordinal = !!B;

	diaSymbol->get_exportIsForwarder(&B);
	forwarder = !!B;

	diaSymbol->get_function(&B);
	function_ = !!B;

	diaSymbol->get_constType(&B);
	const_ = !!B;
}
Sym::Typedef::Typedef(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;

	DWORD D;
	diaSymbol->get_typeId(&D);
	type_symbol = D;

	diaSymbol->get_unmodifiedTypeId(&D);
	unmodified_type_symbol = D;
}
Sym::PublicSymbol::PublicSymbol(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	address.init(diaSymbol);
	Type T{};
	BOOL B = 0;

	T = Type::FUNCTION;
	diaSymbol->get_function(&B);
	if (!B)
	{
		T = Type::OTHER;
		diaSymbol->get_dataExport(&B);
		if (B)
		{
			T = Type::DATA;
		}
	}

	diaSymbol->get_managed(&B);
	managed = !!B;

	diaSymbol->get_msil(&B);
	cil = !!B;
	type = T;
}
Sym::FunctionArg::FunctionArg(IDiaSymbol* dia, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	DWORD D = 0;
	dia->get_typeId(&D);
	type_symbol = D;
}
Sym::Exe::Exe(IDiaSymbol* diaSymbol)  noexcept
	:ctypes(false)
	, architecture(0)
{
	GUID G;
	DWORD D;

	diaSymbol->get_guid(&G);
	OLECHAR* olestr;
	::StringFromCLSID(G, &olestr);
	guid = wstrcvt(olestr);
	::CoTaskMemFree(olestr);

	diaSymbol->get_symIndexId(&D);
	symbol = D;

	diaSymbol->get_signature(&D);
	signature = D;

	diaSymbol->get_age(&D);
	age = D;

	CComBSTR bstr;
	if (SUCCEEDED(diaSymbol->get_symbolsFileName(&bstr)))
		symbols_path = wstrcvt((wchar_t*)bstr);

	BOOL B = 0;
	diaSymbol->get_isCTypes(&B);
	ctypes = !!B;

	diaSymbol->get_isStripped(&B);
	stripped = !!B;

	D = 0;
	diaSymbol->get_machineType(&D);
	architecture = D;

}
Sym::Function::Function(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
	:virtuality(Virtuality::NONE)
{
	DWORD D;
	BOOL B;
	ULONGLONG LL;
	symbol = symIndexId_;

	B = 0;
	diaSymbol->get_hasAlloca(&B);
	alloca_ = !!B;

	B = 0;
	diaSymbol->get_isSafeBuffers(&B);
	safebuffers = !!B;

	B = 0;
	diaSymbol->get_isPGO(&B);
	pgo = !!B;

	B = 0;
	diaSymbol->get_compilerGenerated(&B);
	compiler_generated = !!B;

	diaSymbol->get_hasValidPGOCounts(&B);
	has_pgo_counts = !!B;

	diaSymbol->get_isOptimizedForSpeed(&B);
	optimized_for_speed = !!B;

	diaSymbol->get_PGOEntryCount(&D);
	pgo_entry_count = D;

	diaSymbol->get_PGODynamicInstructionCount(&LL);
	pgo_dyn_instr_count = LL;

	diaSymbol->get_staticSize(&D);
	static_size = D;

	diaSymbol->get_finalLiveStaticSize(&D);
	final_live_static_size = D;

	diaSymbol->get_hasControlFlowCheck(&B);
	control_flow_check = !!B;

	diaSymbol->get_frameSize(&D);
	frame_size = D;

	diaSymbol->get_exceptionHandlerRelativeVirtualAddress(&D);
	eh_address.rv = D;

	diaSymbol->get_hasInlAsm(&B);
	asm_ = !!B;

	diaSymbol->get_hasEH(&B);
	eh = !!B;

	diaSymbol->get_hasEHa(&B);
	eha = !!B;

	diaSymbol->get_hasSEH(&B);
	seh = !!B;

	diaSymbol->get_typeId(&D);
	type_symbol = D;

	diaSymbol->get_hasLongJump(&B);
	longjmp = !!B;

	diaSymbol->get_hasSetJump(&B);
	setjmp_ = !!B;

	diaSymbol->get_hasSecurityChecks(&B);
	security_checks = !!B;

	diaSymbol->get_wasInlined(&B);
	inlined = !!B;

	diaSymbol->get_noInline(&B);
	noinline = !!B;

	diaSymbol->get_noReturn(&B);
	noreturn = !!B;

	diaSymbol->get_isStatic(&B);
	static_ = !!B;

	diaSymbol->get_sealed(&B);
	sealed = !!B;

	diaSymbol->get_constantExport(&B);
	const_export = !!B;

	diaSymbol->get_strictGSCheck(&B);
	strict_gs_check = !!B;

	diaSymbol->get_pure(&B);
	pure_virtual = !!B;

	virtuality = Sym::Function::Virtuality::NONE;
	diaSymbol->get_virtual(&B);
	if (B)
	{
		virtuality = Sym::Function::Virtuality::OVERRIDE;
		diaSymbol->get_intro(&B);
		if (B)
		{
			virtuality = Sym::Function::Virtuality::INTRO;
		}
	}

	diaSymbol->get_notReached(&B);
	unreachable = !!B;

	diaSymbol->get_paramBasePointerRegisterId(&D);
	pbp_regid = D;

	access = Sym::Access::NONE;
	if (S_OK == diaSymbol->get_access(&D))
	{
		access = (Sym::Access)D;
	}

	diaSymbol->get_customCallingConvention(&B);
	custom_call = !!B;

	diaSymbol->get_virtualBaseOffset(&D);
	virtual_base_offset = D;

	diaSymbol->get_noStackOrdering(&B);
	stack_ordering = !B;

	diaSymbol->get_isNaked(&B);
	naked = !!B;

	diaSymbol->get_farReturn(&B);
	far_return = !!B;

	//diaSymbol->get_token(&D);
	//token = D;

	diaSymbol->get_optimizedCodeDebugInfo(&B);
	optimized_debug_info = !!B;

	diaSymbol->get_interruptReturn(&B);
	interrupt_return = !!B;

	diaSymbol->get_inlSpec(&B);
	inline_ = !!B;

	diaSymbol->get_notReached(&B);
	unreachable = !!B;

	diaSymbol->get_framePointerPresent(&B);
	frame_pointer = !!B;

	address.init(diaSymbol);

	diaSymbol->get_localBasePointerRegisterId(&D);
	lbp_regid = D;

}
Sym::InputAssembly::InputAssembly(IDiaInputAssemblyFile* sym)  noexcept
{
	CComBSTR bstr;
	if (S_OK == sym->get_fileName(&bstr))
	{
		filename = wstrcvt((wchar_t*)bstr);
	}
	DWORD D = 0;
	sym->get_index(&D);
	index_ = D;

	BOOL B = 0;
	sym->get_pdbAvailableAtILMerge(&B);
	pdb_available_at_il_merge = !!B;

	D = 0;
	sym->get_timestamp(&D);
	timestamp = D;

	D = 0;
	sym->get_uniqueId(&D);
	uid = D;
}

Sym::Enum::Enum(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	BOOL B;
	DWORD BaseType;
	diaSymbol->get_baseType(&BaseType);
	type = (BuiltinType::Kind)BaseType;

	symbol = symIndexId_;

	diaSymbol->get_packed(&B);
	packed = !!B;

	diaSymbol->get_scoped(&B);
	scoped = !!B;
}
Sym::SourceFile::SourceFile(IDiaSourceFile* src)  noexcept
{
	DWORD id = 0;
	src->get_uniqueId(&id);
	source_id = id;

	CComBSTR str;
	if (SUCCEEDED(src->get_fileName(&str)))
	{
		path = wstrcvt((wchar_t*)str);
	}
}
Sym::Compiland::Compiland(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	memset(this, 0, sizeof(*this));
	symbol = symIndexId_;
	BOOL EditAndContinue = false;
	diaSymbol->get_editAndContinueEnabled(&EditAndContinue);
	edit_and_continue = !!EditAndContinue;


	CComBSTR lib;
	if (diaSymbol->get_libraryName(&lib) == S_OK)
	{
		library = wstrcvt((wchar_t*)lib);
	}

	CComBSTR compiler_;
	if (diaSymbol->get_compilerName(&compiler_) == S_OK)
	{
		compiler = wstrcvt((wchar_t*)compiler_);
	}

	BOOL IsLTCG = false;
	diaSymbol->get_isLTCG(&IsLTCG);
	ltcg = !!IsLTCG;
}

void Sym::Compiland::AppendDetails(IDiaSymbol* diaSymbol)
{
	DWORD D;
	BOOL B;
	static_assert(CV_CFL_X64 == (int)CPU::X64, "Enum mismatch");
	platform = CPU();
	D = 0;
	diaSymbol->get_backEndBuild(&D);
	backend_build = D;

	D = 0;
	diaSymbol->get_backEndMajor(&D);
	backend_major = D;

	D = 0;
	diaSymbol->get_backEndMinor(&D);
	backend_minor = D;

	D = 0;
	diaSymbol->get_frontEndBuild(&D);
	frontend_build = D;

	D = 0;
	diaSymbol->get_frontEndMajor(&D);
	frontend_major = D;

	D = 0;
	diaSymbol->get_frontEndMinor(&D);
	frontend_minor = D;

	B = 0;
	diaSymbol->get_hasDebugInfo(&B);
	debug_info = !!B;

	B = 0;
	diaSymbol->get_isDataAligned(&B);
	data_aligned = !!B;

	B = 0;
	diaSymbol->get_isLTCG(&B);
	ltcg = !!B;

	B = 0;
	diaSymbol->get_isHotpatchable(&B);
	hotpatchable = !!B;

	B = 0;
	diaSymbol->get_isCVTCIL(&B);
	cvtcil = !!B;

	B = 0;
	diaSymbol->get_isMSILNetmodule(&B);
	cil_netmodule = !!B;

	D = 0;
	diaSymbol->get_language(&D);

	static_assert(CV_CFL_HLSL == (DWORD)Language::HLSL, "Enum mismatch");
	static_assert(CV_CFL_C == (DWORD)Language::C, "Enum mismatch");
	language = (Language)D;

	D = 0;
	diaSymbol->get_platform(&D);
	platform = (Sym::CPU) D;

	B = 0;
	diaSymbol->get_hasSecurityChecks(&B);
	security_check = !!B;

	B = 0;
	diaSymbol->get_hasManagedCode(&B);
	managed = !!B;

	D = 0;
	diaSymbol->get_backEndQFE(&D);
	backend_qfe = D;

	D = 0;
	diaSymbol->get_frontEndQFE(&D);
	frontend_qfe = D;

	B = 0;
	diaSymbol->get_isSdl(&B);
	sdl = !!B;

	B = 0;
	diaSymbol->get_isPGO(&B);
	pgo = !!B;
}

Sym::Symbol::Symbol(IDiaSymbol* diaSymbol, unsigned long SymbolID, unsigned char SymTag)  noexcept
{
	symbol = SymbolID;
	tag = (Sym::Tag)SymTag;

	DWORD D;

	D = 0;
	diaSymbol->get_classParentId(&D);
	parent_symbol = D;

	D = 0;
	diaSymbol->get_lexicalParentId(&D);
	lexical_parent_symbol = D;

	CComBSTR Bstr;
	diaSymbol->get_name(&Bstr);
	if (Bstr != nullptr)
	{
		name = wstrcvt((wchar_t*)Bstr);
	}

	ULONGLONG Size = 0;
	diaSymbol->get_length(&Size);
	size = Size;

	D = 0;
	diaSymbol->get_locationType(&D);
	location_type = (Sym::Location) D;
}
Sym::FunctionType::FunctionType(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	BOOL B = false;
	diaSymbol->get_constantExport(&B);
	constant_export = !!B;

	B = false;
	diaSymbol->get_constType(&B);
	const_ = !!B;

	B = false;
	diaSymbol->get_volatileType(&B);
	volatile_ = !!B;

	B = false;
	diaSymbol->get_unalignedType(&B);
	unaligned = !!B;

	B = false;
	diaSymbol->get_constructor(&B);
	is_constructor = !!B;

	DWORD D = 0;
	diaSymbol->get_count(&D);
	param_count = D;

	B = false;
	diaSymbol->get_isCxxReturnUdt(&B);
	cxx_return_udt = !!B;

	B = false;
	diaSymbol->get_isConstructorVirtualBase(&B);
	constructor_virtual_base = !!B;

	B = false;
	diaSymbol->get_constantExport(&B);
	constant_export = !!B;

	D = 0;
	diaSymbol->get_typeId(&D);
	return_type_symbol = D;

	LONG L = 0;
	diaSymbol->get_thisAdjust(&L);
	this_adjust = L;

	DWORD thisid = 0;
	CComPtr<IDiaSymbol> this_type;
	if (S_OK == diaSymbol->get_objectPointerType(&this_type))
	{
		this_type->get_symIndexId(&thisid);
	}
	this_type_symbol = thisid;

	D = 0;
	diaSymbol->get_callingConvention(&D);
	call_convention = (FunctionType::CallConv) D;

}
Sym::SrcRange::SrcRange(uint32_t id_, IDiaLineNumber* line)  noexcept
{
	DWORD D = 0;
	BOOL B = false;

	id = id_;

	line->get_compilandId(&D);
	compiland_symbol = D;

	D = 0;
	line->get_sourceFileId(&D);
	src_file = D;

	D = 0;
	line->get_lineNumber(&D);
	line_begin = D;

	D = 0;
	line->get_lineNumberEnd(&D);
	line_end = D;

	D = 0;
	line->get_columnNumber(&D);
	column_begin = D;

	D = 0;
	line->get_columnNumberEnd(&D);
	column_end = D;

	//address.init(line);

	D = 0;
	line->get_length(&D);
	length = D;

	B = false;
	line->get_statement(&B);
	statement = !!B;

	D = 0;
	line->get_addressOffset(&D);
	address_offset = D;

	D = 0;
	line->get_relativeVirtualAddress(&D);
	address_rv = D;

	D = 0;
	line->get_addressSection(&D);
	address_section = D;

}
Sym::BuiltinType::BuiltinType(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	BOOL B;
	DWORD D;
	symbol = symIndexId_;

	diaSymbol->get_baseType(&D);
	kind = (BuiltinType::Kind) D;

	diaSymbol->get_constType(&B);
	const_ = !!B;

	diaSymbol->get_volatileType(&B);
	volatile_ = !!B;

	diaSymbol->get_unalignedType(&B);
	unaligned = !!B;

	diaSymbol->get_constantExport(&B);
	const_export = !!B;

	D = 0;
	diaSymbol->get_count(&D);
	count = D;

	D = 0;
	diaSymbol->get_arrayIndexTypeId(&D);
	array_index_type_symbol = D;

	D = 0;
	diaSymbol->get_typeId(&D);
	type_symbol = D;
}
Sym::UserType::UserType(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	src_line = 0;
	symbol = symIndexId_;
	DWORD UDTKind = 0;
	diaSymbol->get_udtKind(&UDTKind);
	switch (UDTKind)
	{
	case UdtClass: kind = Sym::UserType::Kind::CLASS; break;
	case UdtInterface: kind = Sym::UserType::Kind::INTERFACE; break;
	case UdtStruct: kind = Sym::UserType::Kind::STRUCT; break;
	case UdtUnion: kind = Sym::UserType::Kind::UNION; break;
	}

	BOOL B = 0;
	diaSymbol->get_constructor(&B);
	constructor = !!B;

	aggregate_type = Aggregate::NONE;
	diaSymbol->get_hfaDouble(&B);
	if (!B)
	{
		diaSymbol->get_hfaFloat(&B);
		if (B)
		{
			aggregate_type = Aggregate::HOMOG_FLOAT;
		}
	}
	else
	{
		aggregate_type = Aggregate::HOMOG_DOUBLE;
	}

	diaSymbol->get_isRefUdt(&B);
	semantics = Semantics::UNKNOWN;
	if (B)
	{
		semantics = Semantics::REFERENCE;
	}
	else
	{
		diaSymbol->get_isValueUdt(&B);
		if (B)
		{
			semantics = Semantics::VALUE;
		}
		else
		{
			diaSymbol->get_isInterfaceUdt(&B);
			if (B)
			{
				semantics = Semantics::INTERFACE;
			}
		}
	}
	diaSymbol->get_constType(&B);
	const_ = !!B;

	diaSymbol->get_volatileType(&B);
	volatile_ = !!B;

	diaSymbol->get_packed(&B);
	packed = !!B;

	diaSymbol->get_intrinsic(&B);
	intrinsic = !!B;

	diaSymbol->get_overloadedOperator(&B);
	overloaded_operators = !!B;

	diaSymbol->get_nested(&B);
	nested = !!B;

	diaSymbol->get_hasNestedTypes(&B);
	has_nested_types = !!B;

	diaSymbol->get_hasAssignmentOperator(&B);
	assignment_operator = !!B;

	diaSymbol->get_hasCastOperator(&B);
	cast_operator = !!B;

	diaSymbol->get_scoped(&B);
	scoped = !!B;

	diaSymbol->get_unalignedType(&B);
	unaligned = !!B;

	DWORD D = 0;
	diaSymbol->get_virtualTableShapeId(&D);
	vtable_shape = D;

	D = 0;
	CComPtr<IDiaSymbol> vtable;
	if (diaSymbol->get_virtualTableShape(&vtable) == S_OK)
	{
		vtable->get_count(&D);
	}
	vtable_count = D;
}
Sym::Data::Data(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	CComVariant Val;
	BOOL B;
	diaSymbol->get_value((VARIANT*)&Val);
	//measurements suggest data are always number values
	VariantChangeType(&Val, &Val, 0, VT_I8);
	if (Val.vt == VT_I8)
	{
		value = Val.llVal;
	}
	else if (Val.vt == VT_I4)
	{
		value = Val.lVal;
	}
	else if (Val.vt == VT_R4)
	{
		value = static_cast<int64_t>(Val.fltVal);
	}
	else if (Val.vt == VT_R8)
	{
		value = static_cast<int64_t>(Val.dblVal);
	}
	symbol = symIndexId_;

	DWORD D = 0;
	diaSymbol->get_dataKind(&D);
	kind = (Kind)D;

	diaSymbol->get_typeId(&D);
	type_symbol = D;
	if (kind == Kind::CONSTANT || kind == Kind::LOCAL || kind == Kind::PARAM || kind == Kind::MEMBER)
	{
		address.rv = 0;
	}
	else
	{
		address.init(diaSymbol);
	}

	diaSymbol->get_registerId(&D);
	register_id = D;

	diaSymbol->get_constantExport(&B);
	const_export = !!B;

	diaSymbol->get_bitPosition(&D);
	bit_position = D;

	LONG L = 0;
	diaSymbol->get_offset(&L);
	offset = L;
}
Sym::Label::Label(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	address.init(diaSymbol);
}
Sym::Callsite::Callsite(IDiaSession*, IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;

	address.init(diaSymbol);

	DWORD d = 0;
	diaSymbol->get_lexicalParentId(&d);
	target_symbol = d;
}
Sym::Pointer::Pointer(IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	symbol = symIndexId_;
	DWORD D;
	BOOL B;
	diaSymbol->get_typeId(&D);
	type_symbol = D;

	B = false;
	diaSymbol->get_isWinRTPointer(&B);
	kind = Kind::WINRT_HAT;
	if (!B)
	{
		kind = Kind::R_REF;
		diaSymbol->get_RValueReference(&B);
		if (!B)
		{
			kind = Kind::L_REF;
			diaSymbol->get_reference(&B);
			if (!B)
			{
				kind = Kind::PTR;
			}
		}
	}

	B = false;
	diaSymbol->get_unalignedType(&B);
	unaligned = !!B;

	B = false;
	diaSymbol->get_volatileType(&B);
	volatile_ = !!B;

	B = false;
	diaSymbol->get_constType(&B);
	const_ = !!B;

	B = false;
	diaSymbol->get_restrictedType(&B);
	restrict_ = !!B;

	B = false;
	diaSymbol->get_constantExport(&B);
	constant_export = !!B;

	B = false;
	diaSymbol->get_isPointerToDataMember(&B);
	member_type = MemberType::NONE;
	if (B)
	{
		member_type = MemberType::DATA;
	}
	else
	{
		diaSymbol->get_isPointerToMemberFunction(&B);
		if (B)
		{
			member_type = MemberType::FUNCTION;
		}
	}

	B = 0;
	diaSymbol->get_isMultipleInheritance(&B);
	inheritance = Inheritance::NONE;
	if (B)
	{
		inheritance = Inheritance::MULTIPLE;
	}
	else
	{
		diaSymbol->get_isSingleInheritance(&B);
		if (B)
		{
			inheritance = Inheritance::SINGLE;
		}
	}

	B = 0;
	diaSymbol->get_isVirtualInheritance(&B);
	virtual_inheritance = !!B;

	D = 0;
	diaSymbol->get_unmodifiedTypeId(&D);
	unmodified_type_symbol = D;
}

Sym::CompilandEnv::CompilandEnv(IDiaSymbol* Symbol)  noexcept
{
	DWORD Compiland = 0;
	Symbol->get_lexicalParentId(&Compiland);
	compiland_symbol = Compiland;

	CComBSTR txt;
	Symbol->get_name(&txt);
	option_name = wstrcvt((wchar_t*)txt);

	CComVariant v;
	Symbol->get_value((VARIANT*)&v);
	if (v.vt == VT_BSTR)
	{
		value = wstrcvt((wchar_t*)v.bstrVal);
	}
}
Sym::InjectedSource::InjectedSource(IDiaInjectedSource* src)  noexcept
{
	ULONGLONG L = 0;
	src->get_length(&L);
	length = L;

	BYTE buf[256];
	DWORD num = 0;
	src->get_source(255, &num, buf);
	buf[num] = 0;
	text = (char*)buf;
}

Sym::Thunk::Thunk(IDiaSession* dia, IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept
{
	ordinal = Ordinal::NONE;
	symbol = symIndexId_;
	address.init(diaSymbol);


	DWORD D;
	diaSymbol->get_thunkOrdinal(&D);
	ordinal = (Ordinal)D;

	diaSymbol->get_targetRelativeVirtualAddress(&D);
	target.rv = D;

	target_symbol = 0;
	CComPtr<IDiaSymbol> targetsym;
	if (S_OK == dia->findSymbolByRVA(D, SymTagNull, &targetsym) && targetsym)
	{
		targetsym->get_symIndexId(&D);
		target_symbol = D;
	}

}

Sym::Frame::Frame(IDiaFrameData* frame)  noexcept
{
	CComBSTR str;
	if (frame->get_program(&str) == S_OK)
	{
		program = wstrcvt((wchar_t*)str);
	}
	address.init(frame);

	DWORD D = 0;
	frame->get_lengthBlock(&D);
	length_block = D;

	D = 0;
	frame->get_lengthLocals(&D);
	length_locals = D;

	D = 0;
	frame->get_lengthParams(&D);
	length_params = D;


	D = 0;
	frame->get_maxStack(&D);
	max_stack = D;

	D = 0;
	frame->get_lengthProlog(&D);
	length_prolog = D;

	D = 0;
	frame->get_lengthSavedRegisters(&D);
	length_saved_registers = D;

	D = 0;
	frame->get_type(&D);
	type_symbol = D;

	BOOL B = 0;
	frame->get_systemExceptionHandling(&B);
	exceptions_system = !!B;

	frame->get_cplusplusExceptionHandling(&B);
	exceptions_cxx = !!B;

	frame->get_functionStart(&B);
	function_start = !!B;

	frame->get_allocatesBasePointer(&B);
	allocate_base_pointer = !!B;

}

Sym::VTablePtr::VTablePtr(IDiaSymbol* diaSymbol, uint32_t symIndexId) noexcept
{
	DWORD D = 0;
	BOOL B = 0;
	LONG L = 0;

	/*
	these appear to always return 0/false
	diaSymbol->get_constType(&B);
	const_ = !!B;

	diaSymbol->get_volatileType(&B);
	volatile_ = !!B;

	diaSymbol->get_unalignedType(&B);
	unaligned = !!B;

	diaSymbol->get_constantExport(&B);
	const_export = !!B;
	*/

	diaSymbol->get_typeId(&D);
	type_symbol = D;

	symbol = symIndexId;

}


Sym::Friend::Friend(IDiaSymbol* diaSymbol, uint32_t symIndexId) noexcept
{
	symbol = symIndexId;
	DWORD D = 0;
	diaSymbol->get_typeId(&D);
	type_symbol = D;
}
namespace
{
	class Dia2SymbolProvider
	{
		SymbolData& Result;

		std::unordered_map<DWORD, unsigned int> SymCompilandMap;

		void ReadSections(IDiaEnumDebugStreamData* enumSectionHeaders)
		{
			int section_index = 1;

			while (true)
			{
				ULONG numFetched = 1;
				DWORD bytesRead = 0;
				IMAGE_SECTION_HEADER imageSectionHeader;
				memset(&imageSectionHeader, 0, sizeof(imageSectionHeader));

				enumSectionHeaders->Next(numFetched, sizeof(imageSectionHeader), &bytesRead, (BYTE*)&imageSectionHeader, &numFetched);
				if (numFetched < 1 || bytesRead != sizeof(imageSectionHeader))
					break;

				Sym::AddrSection s;
				for (int i = 0; i<ARRAYSIZE(imageSectionHeader.Name); ++i)
				{
					if (imageSectionHeader.Name[i] != '\0')
					{
						s.name += (char)imageSectionHeader.Name[i];
					}
					else
					{
						break;
					}
				}

				s.section_index = section_index;
				s.line_numbers = imageSectionHeader.NumberOfLinenumbers;
				s.size = imageSectionHeader.SizeOfRawData;
				s.relocations = imageSectionHeader.NumberOfRelocations;
				s.comdat = (imageSectionHeader.Characteristics & IMAGE_SCN_LNK_COMDAT) != 0;
				s.readable = (imageSectionHeader.Characteristics & IMAGE_SCN_MEM_READ) != 0;
				s.writable = (imageSectionHeader.Characteristics & IMAGE_SCN_MEM_WRITE) != 0;
				s.executable = (imageSectionHeader.Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0;
				s.discardable = (imageSectionHeader.Characteristics & IMAGE_SCN_MEM_DISCARDABLE) != 0;
				Result.AddrSection.push_back(s);

				++section_index;
			}
		}

		void ReadStreams(IDiaSession* session)
		{
			CComPtr<IDiaEnumDebugStreams> streamEnum = nullptr;
			session->getEnumDebugStreams(&streamEnum);
			while (streamEnum)
			{
				ULONG numFetched = 1;
				CComPtr<IDiaEnumDebugStreamData> enumStreamData = nullptr;
				streamEnum->Next(numFetched, &enumStreamData, &numFetched);
				if (enumStreamData == nullptr || numFetched < 1)
					break;
				CComBSTR enumDataName;
				enumStreamData->get_name(&enumDataName);
				if (wcscmp(enumDataName, L"SECTIONHEADERS") == 0)
				{
					ReadSections(enumStreamData);
				}
			}
		}
		void ReadLines(IDiaLineNumber* line)
		{
			Result.SrcRange.emplace_back((uint32_t)Result.SrcRange.size(), line);
		}
		void ReadSource(IDiaSourceFile* item)
		{
			Result.SourceFile.emplace_back(item);
			DWORD file_id = 0;
			item->get_uniqueId(&file_id);
			CComPtr<IDiaEnumSymbols> enumerate_compilands = nullptr;
			if (item->get_compilands(&enumerate_compilands) == S_OK)
			{
				while (true)
				{
					CComPtr<IDiaSymbol> compilands[64];
					DWORD fetched = 0;
					if (enumerate_compilands->Next(64, &compilands[0], &fetched) == S_OK)
					{
						for (DWORD i = 0; i < fetched; ++i)
						{
							DWORD compiland_id = 0;
							compilands[i]->get_symIndexId(&compiland_id);
							Result.Included.emplace_back(compiland_id, file_id);
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		void ReadSymbol(IDiaSymbol* diaSymbol)
		{
			DWORD symIndexId = 0;
			diaSymbol->get_symIndexId(&symIndexId);

			DWORD SymTag = 0;
			diaSymbol->get_symTag(&SymTag);

			Result.Symbol.emplace_back(diaSymbol, symIndexId, (unsigned char)SymTag);

			switch (SymTag)
			{
			case SymTagExe:					Result.Exe.emplace_back(diaSymbol);									break;
			case SymTagCompiland:			ReadCompilandSymbol(diaSymbol, symIndexId);							break;
			case SymTagCompilandDetails:	ReadCompilandDetailsSymbol(diaSymbol);								break;
			case SymTagCompilandEnv:		Result.CompilandEnv.emplace_back(diaSymbol);						break;
			case SymTagFunction:			Result.Function.emplace_back(diaSymbol, symIndexId);				break;
			case SymTagBlock:				Result.Block.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagData:				Result.Data.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagAnnotation:																				break;
			case SymTagLabel:				Result.Label.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagPublicSymbol:		Result.PublicSymbol.emplace_back(diaSymbol, symIndexId);			break;
			case SymTagUDT:					ReadUDTSymbol(diaSymbol, symIndexId);								break;
			case SymTagEnum:				Result.Enum.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagFunctionType:		Result.FunctionType.emplace_back(diaSymbol, symIndexId);			break;
			case SymTagPointerType:			Result.Pointer.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagArrayType:			Result.Array.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagBaseType:			Result.BuiltinType.emplace_back(diaSymbol, symIndexId);				break;
			case SymTagTypedef:				Result.Typedef.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagBaseClass:			Result.BaseClass.emplace_back(diaSymbol);							break;
			case SymTagFriend:				Result.Friend.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagFunctionArgType:		Result.FunctionArg.emplace_back(diaSymbol, symIndexId);				break;
			case SymTagFuncDebugStart:																			break;
			case SymTagFuncDebugEnd:																			break;
			case SymTagUsingNamespace:																			break;
			case SymTagVTableShape:																				break;
			case SymTagVTable:				Result.VTablePtr.emplace_back(diaSymbol, symIndexId);				break;
			case SymTagCustom:																					break;
			case SymTagThunk:				Result.Thunk.emplace_back(Provider.session, diaSymbol, symIndexId);	break;
			case SymTagCustomType:																				break;
			case SymTagManagedType:																				break;
			case SymTagDimension:																				break;
			case SymTagCallSite:			Result.Callsite.emplace_back(Provider.session, diaSymbol, symIndexId);		break;
			case SymTagInlineSite:			Result.Inlined.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagBaseInterface:																			break;
			case SymTagVectorType:																				break;
			case SymTagMatrixType:																				break;
			case SymTagHLSLType:																				break;
			case SymTagCaller:																					break;
			case SymTagCallee:																					break;
			case SymTagExport:				Result.Export.emplace_back(diaSymbol, symIndexId);					break;
			case SymTagHeapAllocationSite:	Result.HeapAllocation.emplace_back(diaSymbol, symIndexId);			break;
			case SymTagCoffGroup:																				break;
			}


		}

		void ReadUDTSymbol(IDiaSymbol* diaSymbol, uint32_t symIndexId_)
		{
			Result.UserType.emplace_back(diaSymbol, symIndexId_);
			CComPtr<IDiaLineNumber> line = nullptr;

			//this will cause double-counting of src lines
			//entries added here will be duplicated by ReadLines
			//not sure how to fix that...
			if (SUCCEEDED(diaSymbol->getSrcLineOnTypeDefn(&line)) && line)
			{
				auto id = static_cast<uint32_t>(Result.SrcRange.size());
				Result.UserType.back().src_line = id;
				Result.SrcRange.emplace_back(id, line);
			}
		}

		void ReadCompilandDetailsSymbol(IDiaSymbol* diaSymbol)
		{
			DWORD Compiland = 0;
			diaSymbol->get_lexicalParentId(&Compiland);
			Sym::Compiland& Item = Result.Compiland[SymCompilandMap[Compiland]];
			Item.AppendDetails(diaSymbol);
		}
		void ReadCompilandSymbol(IDiaSymbol* diaSymbol, uint32_t symIndexId_)
		{
			SymCompilandMap[symIndexId_] = static_cast<unsigned int>(Result.Compiland.size());
			Result.Compiland.emplace_back(diaSymbol, symIndexId_);
		}

	public:
		DIA2::Provider Provider;
		Dia2SymbolProvider(SymbolData& inResult)
			:Result(inResult)
		{
		}
		struct ReadSourceHelper
		{
			Dia2SymbolProvider& self;
			ReadSourceHelper(Dia2SymbolProvider& in) : self(in) {}
			void init(LONG n) { self.Result.SourceFile.reserve(n); }
			template<class T> void element(T&& element) { self.ReadSource(element); }
		};

		struct ReadSymbolHelper
		{
			Dia2SymbolProvider& self;
			ReadSymbolHelper(Dia2SymbolProvider& in) : self(in) {}
			void init(LONG n) { self.Result.Symbol.reserve(n); }
			template<class T> void element(T&& element) { self.ReadSymbol(element); }
		};
		struct ReadLineHelper
		{
			Dia2SymbolProvider& self;
			ReadLineHelper(Dia2SymbolProvider& in) : self(in) {}
			void init(LONG n) { self.Result.SrcRange.reserve(n); }
			template<class T> void element(T&& element) { self.ReadLines(element); }
		};
		void ReadSymbols()
		{
			no_addresses = getFlag("-noaddress");
			Result.Symbol.emplace_back();
			ReadStreams(Provider.session);
			DIA2::ReadTables(Provider.session,
				Result.ReadSectionContrib(),
				Result.ReadInjectedSource(),
				ReadSourceHelper(*this),
				ReadSymbolHelper(*this),
				Result.ReadSegment(),
				Result.ReadInputAssembly(),
				Result.ReadFrame(),
				ReadLineHelper(*this));
		}
	};
}

namespace DIA2
{
	void ReadSymbols(const char* File, SymbolData& Result)
	{
		Dia2SymbolProvider dia(Result);
		if (dia.Provider.load(File))
		{
			dia.ReadSymbols();
		}
	}
}
