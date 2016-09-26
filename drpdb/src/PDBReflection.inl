#ifndef BEGIN_STRUCT
#define BEGIN_STRUCT(...)
#endif

#ifndef MEMBER
#define MEMBER(...)
#endif

#ifndef UNIQUE_MEMBER
#define UNIQUE_MEMBER(...) MEMBER(__VA_ARGS__)
#endif

#ifndef END_STRUCT
#define END_STRUCT(...)
#endif

#ifndef BEGIN_ENUMERATION
#define BEGIN_ENUMERATION(...)
#endif

#ifndef END_ENUMERATION
#define END_ENUMERATION(...)
#endif

#ifndef ENUMERATOR
#define ENUMERATOR(...)
#endif

BEGIN_STRUCT(BuiltinType, builtins)
		UNIQUE_MEMBER(symbol)
		MEMBER(array_index_type_symbol)
		MEMBER(type_symbol)
		MEMBER(count)
		MEMBER(kind)
		MEMBER(unaligned)
		MEMBER(const_)
		MEMBER(volatile_)
		MEMBER(const_export)
END_STRUCT()
BEGIN_STRUCT(Frame, frames)
	MEMBER(program)
	MEMBER(address)
	MEMBER(length_block)
	MEMBER(length_locals)
	MEMBER(length_params)
	MEMBER(max_stack)
	MEMBER(length_prolog)
	MEMBER(length_saved_registers)
	MEMBER(type_symbol)
	MEMBER(exceptions_system)
	MEMBER(exceptions_cxx)
	MEMBER(function_start)
	MEMBER(allocate_base_pointer)
END_STRUCT()
BEGIN_STRUCT(Label, labels)
	UNIQUE_MEMBER(symbol)
	MEMBER(address)
END_STRUCT()
BEGIN_STRUCT(FunctionType, function_types)
	UNIQUE_MEMBER(symbol)
	MEMBER(volatile_)
	MEMBER(const_)
	MEMBER(unaligned)
	MEMBER(this_adjust)
	MEMBER(param_count)
	MEMBER(is_constructor)
	MEMBER(type_symbol)
	MEMBER(this_type_symbol)
	MEMBER(cxx_return_udt)
	MEMBER(constructor_virtual_base)
	MEMBER(constant_export)
	MEMBER(call_convention)
END_STRUCT()
BEGIN_STRUCT(Function, functions)
	UNIQUE_MEMBER(symbol)
	MEMBER(virtual_base_offset)
	MEMBER(type_symbol)
	MEMBER(access)
	MEMBER(call_convention)
	MEMBER(virtuality)
	MEMBER(pgo_dyn_instr_count)
	MEMBER(static_size)
	MEMBER(pbp_regid)
	MEMBER(lbp_regid)
	MEMBER(final_live_static_size)
	MEMBER(frame_size)
	MEMBER(address)
	MEMBER(exception_handler)
	MEMBER(pgo_entry_count)
	MEMBER(control_flow_check)
	MEMBER(exceptions)
	MEMBER(sealed)
	MEMBER(security_checks)
	MEMBER(static_)
	MEMBER(pure_virtual)
	MEMBER(inline_)
	MEMBER(inlined)
	MEMBER(noinline)
	MEMBER(noreturn)
	MEMBER(unreachable)
	MEMBER(setjmp_)
	MEMBER(asm_)
	MEMBER(alloca_)
	MEMBER(const_export)
	MEMBER(strict_gs_check)
	MEMBER(longjmp)
	MEMBER(eh)
	MEMBER(eha)
	MEMBER(seh)
	MEMBER(optimized_debug_info)
	MEMBER(frame_pointer)
	MEMBER(interrupt_return)
	MEMBER(far_return)
	MEMBER(naked)
	MEMBER(custom_call)
	MEMBER(stack_ordering)
	MEMBER(safebuffers)
	MEMBER(pgo)
	MEMBER(has_pgo_counts)
	MEMBER(optimized_for_speed)
	MEMBER(compiler_generated)
END_STRUCT()
BEGIN_STRUCT(PublicSymbol, public_symbols)
	UNIQUE_MEMBER(symbol);
	MEMBER(type)
	MEMBER(address)
	MEMBER(managed)
	MEMBER(msil)
END_STRUCT()
BEGIN_STRUCT(Data, data)
	UNIQUE_MEMBER(symbol)
	MEMBER(value)
	MEMBER(type_symbol)
	MEMBER(offset)
	MEMBER(address)
	MEMBER(register_id)
	MEMBER(bit_position)
	MEMBER(kind)
	MEMBER(const_export)
END_STRUCT()
BEGIN_STRUCT(Compiland, compilands)
	UNIQUE_MEMBER(symbol)
	MEMBER(library)
	MEMBER(compiler)
	MEMBER(backend_build)
	MEMBER(backend_major)
	MEMBER(backend_minor)
	MEMBER(frontend_build)
	MEMBER(frontend_major)
	MEMBER(frontend_minor)
	MEMBER(frontend_qfe)
	MEMBER(backend_qfe)
	MEMBER(language)
	MEMBER(platform)
	MEMBER(security_check)
	MEMBER(managed)
	MEMBER(debug_info)
	MEMBER(edit_and_continue)
	MEMBER(ltcg)
	MEMBER(sdl)
	MEMBER(pgo)
	MEMBER(data_aligned)
	MEMBER(hotpatchable)
	MEMBER(cvtcil)
	MEMBER(msil_netmodule)
END_STRUCT()
BEGIN_STRUCT(InjectedSource, injected_src)
	MEMBER(length)
	MEMBER(text)
END_STRUCT()
BEGIN_STRUCT(SourceFile, src_files)
	UNIQUE_MEMBER(source_id)
	MEMBER(path)
END_STRUCT()

BEGIN_STRUCT(SrcRange, src_lines)
	MEMBER(compiland)
	MEMBER(src_file)
	MEMBER(line_begin)
	MEMBER(line_end)
	MEMBER(column_begin)
	MEMBER(column_end)
	MEMBER(address)
	MEMBER(length)
	MEMBER(statement)
END_STRUCT()
BEGIN_STRUCT(InputAssembly, input_assemblies)
	MEMBER(filename)
	MEMBER(index_)
	MEMBER(timestamp)
	MEMBER(uid)
	MEMBER(pdb_available_at_il_merge)
END_STRUCT()
BEGIN_STRUCT(CompilandEnv, compiland_env)
	MEMBER(compiland_symbol)
	MEMBER(option_name)
	MEMBER(value)
END_STRUCT()
BEGIN_STRUCT(Symbol, symbols)
	MEMBER(name)
	UNIQUE_MEMBER(symbol)
	MEMBER(lexical_parent_symbol)
	MEMBER(parent_symbol)
	MEMBER(size)
	MEMBER(tag)
	MEMBER(location_type)
END_STRUCT()

BEGIN_STRUCT(AddrSection, sections)
	UNIQUE_MEMBER(section_index)
	MEMBER(size)
	MEMBER(line_numbers)
	MEMBER(name)
	MEMBER(relocations)
	MEMBER(comdat)
	MEMBER(executable)
	MEMBER(readable)
	MEMBER(writable)
	MEMBER(discardable)
END_STRUCT()
BEGIN_STRUCT(Included, included)
	MEMBER(compiland)
	MEMBER(source_id)
END_STRUCT()
BEGIN_STRUCT(UserType, userTypes)
	UNIQUE_MEMBER(symbol)
	MEMBER(src_line)
	MEMBER(vtable_size)
	MEMBER(kind)
	MEMBER(semantics)
	MEMBER(aggregate_type)
	MEMBER(packed)
	MEMBER(unaligned)
	MEMBER(const_)
	MEMBER(volatile_)
	MEMBER(overloaded_operators)
	MEMBER(nested)
	MEMBER(has_nested_types)
	MEMBER(assignment_operator)
	MEMBER(cast_operator)
	MEMBER(scoped)
	MEMBER(constructor)
END_STRUCT()

BEGIN_STRUCT(Enum, enumerations)
	UNIQUE_MEMBER(symbol)
	MEMBER(unmodified_type_symbol)
	MEMBER(type_symbol)
	MEMBER(type)
	MEMBER(packed)
	MEMBER(scoped)
END_STRUCT()

BEGIN_STRUCT(Pointer, pointers)
UNIQUE_MEMBER(symbol)
MEMBER(type_symbol)
MEMBER(unmodified_type_symbol)
MEMBER(unaligned)
MEMBER(kind)
MEMBER(inheritance)
MEMBER(member_type)
MEMBER(const_)
MEMBER(volatile_)
MEMBER(restrict_)
MEMBER(constant_export)
MEMBER(virtual_inheritance)
END_STRUCT()

BEGIN_STRUCT(BaseClass, baseClasses)
MEMBER(child_symbol)
MEMBER(parent_symbol)
MEMBER(offset)
MEMBER(vdisp_index)
MEMBER(vbase_type_symbol)
MEMBER(vbase_offset)
MEMBER(virtual_)
MEMBER(indirect_virtual)
MEMBER(access)
END_STRUCT()

BEGIN_STRUCT(Thunk, thunks)
UNIQUE_MEMBER(symbol)
MEMBER(ordinal)
MEMBER(address)
MEMBER(target)
MEMBER(target_symbol)
END_STRUCT()

BEGIN_STRUCT(FunctionArg, arguments)
UNIQUE_MEMBER(symbol)
MEMBER(type_symbol)
END_STRUCT()

BEGIN_STRUCT(Block, blocks)
UNIQUE_MEMBER(symbol)
MEMBER(address)
END_STRUCT()

BEGIN_STRUCT(HeapAllocation, heap_allocs)
UNIQUE_MEMBER(symbol)
MEMBER(address)
MEMBER(type_symbol)
END_STRUCT()

BEGIN_STRUCT(Export, exports)
UNIQUE_MEMBER(symbol)
MEMBER(address_offset)
MEMBER(rank)
MEMBER(ordinal)
MEMBER(const_export)
MEMBER(data_export)
MEMBER(private_export)
MEMBER(noname)
MEMBER(explicit_ordinal)
MEMBER(forwarder)
MEMBER(function_)
MEMBER(const_)
END_STRUCT()

BEGIN_STRUCT(Exe, executable)
MEMBER(guid)
MEMBER(symbols_path)
UNIQUE_MEMBER(symbol)
MEMBER(age)
MEMBER(ctypes)
MEMBER(stripped)
MEMBER(architecture)
MEMBER(signature)
END_STRUCT()

BEGIN_STRUCT(Typedef, typedefs)
	UNIQUE_MEMBER(symbol)
	MEMBER(type_symbol)
	MEMBER(unmodified_type_symbol)
END_STRUCT()
BEGIN_STRUCT(SectionContrib, section_contrib)
	MEMBER(compiland_symbol)
	MEMBER(data_crc)
	MEMBER(length)
	MEMBER(address)
	MEMBER(relocations_crc)
	MEMBER(code)
	MEMBER(code_16bit)
	MEMBER(comdat)
	MEMBER(executable)
	MEMBER(discardable)
	MEMBER(initialized_data)
	MEMBER(uninitialized_data)
	MEMBER(cached)
	MEMBER(paged)
	MEMBER(readable)
	MEMBER(writeable)
	MEMBER(remove)
	MEMBER(share)
END_STRUCT()
BEGIN_STRUCT(Inlined, inlined)
	UNIQUE_MEMBER(symbol)
	MEMBER(type_symbol)
	MEMBER(pgo_edges)
	MEMBER(address)
END_STRUCT()
BEGIN_STRUCT(Array, arrays)
	UNIQUE_MEMBER(symbol)
	MEMBER(index_type_symbol)
	MEMBER(count)
	MEMBER(rank)
	MEMBER(type_symbol)
END_STRUCT()
BEGIN_STRUCT(Segment, segments)
	MEMBER(address_rv)
	MEMBER(address_v)
	MEMBER(address_section)
	MEMBER(frame)
	MEMBER(length)
	MEMBER(offset)
	MEMBER(executable)
	MEMBER(readable)
	MEMBER(writable)
END_STRUCT()
BEGIN_STRUCT(Callsite, calls)
	UNIQUE_MEMBER(symbol)
	MEMBER(target_symbol)
	MEMBER(address)
END_STRUCT()
BEGIN_ENUMERATION(PublicSymbol::Type)
	ENUMERATOR(PublicSymbol::Type, FUNCTION)
	ENUMERATOR(PublicSymbol::Type, DATA)
	ENUMERATOR(PublicSymbol::Type, OTHER)
END_ENUMERATION()
BEGIN_ENUMERATION(AddrSection::Kind)
	ENUMERATOR(AddrSection::Kind, UNKNOWN)
	ENUMERATOR(AddrSection::Kind, DATA)
	ENUMERATOR(AddrSection::Kind, BSS)
	ENUMERATOR(AddrSection::Kind, CODE)
	ENUMERATOR(AddrSection::Kind, READDATA)
END_ENUMERATION()
 
BEGIN_ENUMERATION(Language)
	ENUMERATOR(Language, C)
	ENUMERATOR(Language, CXX)
	ENUMERATOR(Language, FORTRAN)
	ENUMERATOR(Language, MASM)
	ENUMERATOR(Language, PASCAL)
	ENUMERATOR(Language, BASIC)
	ENUMERATOR(Language, COBOL)
	ENUMERATOR(Language, LINK)
	ENUMERATOR(Language, CVTRES)
	ENUMERATOR(Language, CVTPGD)
	ENUMERATOR(Language, CSHARP)
	ENUMERATOR(Language, VB)
	ENUMERATOR(Language, ILASM)
	ENUMERATOR(Language, JAVA)
	ENUMERATOR(Language, JS)
	ENUMERATOR(Language, MSIL)
	ENUMERATOR(Language, HLSL)
END_ENUMERATION()
BEGIN_ENUMERATION(UserType::Semantics)
	ENUMERATOR(UserType::Semantics, UNKNOWN)
	ENUMERATOR(UserType::Semantics, VALUE)
	ENUMERATOR(UserType::Semantics, REFERENCE)
	ENUMERATOR(UserType::Semantics, INTERFACE)
END_ENUMERATION();
BEGIN_ENUMERATION(Thunk::Ordinal)
	ENUMERATOR(Thunk::Ordinal, NONE)
	ENUMERATOR(Thunk::Ordinal, ADJUSTOR)
	ENUMERATOR(Thunk::Ordinal, VCALL)
	ENUMERATOR(Thunk::Ordinal, PCODE)
	ENUMERATOR(Thunk::Ordinal, LOAD)
	ENUMERATOR(Thunk::Ordinal, TRAMPOLINE_INCREMENTAL)
	ENUMERATOR(Thunk::Ordinal, TRAMPOLINE_BRANCHISLAND)
END_ENUMERATION()

BEGIN_ENUMERATION(Tag)
	ENUMERATOR(Tag, Unknown)
	ENUMERATOR(Tag, Exe)
	ENUMERATOR(Tag, Compiland)
	ENUMERATOR(Tag, CompilandDetails)
	ENUMERATOR(Tag, CompilandEnv)
	ENUMERATOR(Tag, Function)
	ENUMERATOR(Tag, Block)
	ENUMERATOR(Tag, Data)
	ENUMERATOR(Tag, Annotation)
	ENUMERATOR(Tag, Label)
	ENUMERATOR(Tag, PublicSymbol)
	ENUMERATOR(Tag, UDT)
	ENUMERATOR(Tag, Enum)
	ENUMERATOR(Tag, FunctionType)
	ENUMERATOR(Tag, PointerType)
	ENUMERATOR(Tag, ArrayType)
	ENUMERATOR(Tag, BaseType)
	ENUMERATOR(Tag, Typedef)
	ENUMERATOR(Tag, BaseClass)
	ENUMERATOR(Tag, Friend)
	ENUMERATOR(Tag, FunctionArgType)
	ENUMERATOR(Tag, FuncDebugStart)
	ENUMERATOR(Tag, FuncDebugEnd)
	ENUMERATOR(Tag, UsingNamespace)
	ENUMERATOR(Tag, VTableShape)
	ENUMERATOR(Tag, VTable)
	ENUMERATOR(Tag, Custom)
	ENUMERATOR(Tag, Thunk)
	ENUMERATOR(Tag, CustomType)
	ENUMERATOR(Tag, ManagedType)
	ENUMERATOR(Tag, Dimension)
	ENUMERATOR(Tag, CallSite)
	ENUMERATOR(Tag, InlineSite)
	ENUMERATOR(Tag, BaseInterface)
	ENUMERATOR(Tag, VectorType)
	ENUMERATOR(Tag, MatrixType)
	ENUMERATOR(Tag, HLSLType)
	ENUMERATOR(Tag, Caller)
	ENUMERATOR(Tag, Callee)
	ENUMERATOR(Tag, Export)
	ENUMERATOR(Tag, HeapAllocationSite)
	ENUMERATOR(Tag, CoffGroup)
	ENUMERATOR(Tag, Max)
END_ENUMERATION()
BEGIN_ENUMERATION(Data::Kind)
	ENUMERATOR(Data::Kind, UNKNOWN)
	ENUMERATOR(Data::Kind, LOCAL)
	ENUMERATOR(Data::Kind, STATICLOCAL)
	ENUMERATOR(Data::Kind, PARAM)
	ENUMERATOR(Data::Kind, OBJECTPTR)
	ENUMERATOR(Data::Kind, FILESTATIC)
	ENUMERATOR(Data::Kind, GLOBAL)
	ENUMERATOR(Data::Kind, MEMBER)
	ENUMERATOR(Data::Kind, STATICMEMBER)
	ENUMERATOR(Data::Kind, CONSTANT)
END_ENUMERATION()

BEGIN_ENUMERATION(BuiltinType::Kind)
	ENUMERATOR(BuiltinType::Kind, NONE)
	ENUMERATOR(BuiltinType::Kind, VOID)
	ENUMERATOR(BuiltinType::Kind, CHAR)
	ENUMERATOR(BuiltinType::Kind, WCHAR)
	ENUMERATOR(BuiltinType::Kind, INT)
	ENUMERATOR(BuiltinType::Kind, UINT)
	ENUMERATOR(BuiltinType::Kind, FLOAT)
	ENUMERATOR(BuiltinType::Kind, BCD)
	ENUMERATOR(BuiltinType::Kind, BOOL)
	ENUMERATOR(BuiltinType::Kind, LONG)
	ENUMERATOR(BuiltinType::Kind, ULONG)
	ENUMERATOR(BuiltinType::Kind, CURRENCY)
	ENUMERATOR(BuiltinType::Kind, DATE)
	ENUMERATOR(BuiltinType::Kind, VARIANT)
	ENUMERATOR(BuiltinType::Kind, COMPLEX)
	ENUMERATOR(BuiltinType::Kind, BIT)
	ENUMERATOR(BuiltinType::Kind, BSTR)
	ENUMERATOR(BuiltinType::Kind, HRESULT)
	ENUMERATOR(BuiltinType::Kind, CHAR16) 
	ENUMERATOR(BuiltinType::Kind, CHAR32) 
END_ENUMERATION()
BEGIN_ENUMERATION(Function::CallConv)
	ENUMERATOR(Function::CallConv, NEAR_C) 
	ENUMERATOR(Function::CallConv, FAR_C) 
	ENUMERATOR(Function::CallConv, NEAR_PASCAL) 
	ENUMERATOR(Function::CallConv, FAR_PASCAL) 
	ENUMERATOR(Function::CallConv, NEAR_FAST) 
	ENUMERATOR(Function::CallConv, FAR_FAST) 
	ENUMERATOR(Function::CallConv, SKIPPED) 
	ENUMERATOR(Function::CallConv, NEAR_STD) 
	ENUMERATOR(Function::CallConv, FAR_STD) 
	ENUMERATOR(Function::CallConv, NEAR_SYS) 
	ENUMERATOR(Function::CallConv, FAR_SYS) 
	ENUMERATOR(Function::CallConv, THISCALL) 
	ENUMERATOR(Function::CallConv, MIPSCALL) 
	ENUMERATOR(Function::CallConv, GENERIC) 
	ENUMERATOR(Function::CallConv, ALPHACALL) 
	ENUMERATOR(Function::CallConv, PPCCALL) 
	ENUMERATOR(Function::CallConv, SHCALL) 
	ENUMERATOR(Function::CallConv, ARMCALL) 
	ENUMERATOR(Function::CallConv, AM33CALL) 
	ENUMERATOR(Function::CallConv, TRICALL) 
	ENUMERATOR(Function::CallConv, SH5CALL) 
	ENUMERATOR(Function::CallConv, M32RCALL) 
	ENUMERATOR(Function::CallConv, CLRCALL) 
	ENUMERATOR(Function::CallConv, INLINE) 
	ENUMERATOR(Function::CallConv, NEAR_VECTOR) 
	ENUMERATOR(Function::CallConv, RESERVED)
END_ENUMERATION()
BEGIN_ENUMERATION(UserType::Kind)
	ENUMERATOR(UserType::Kind, STRUCT)
	ENUMERATOR(UserType::Kind, CLASS)
	ENUMERATOR(UserType::Kind, UNION)
	ENUMERATOR(UserType::Kind, INTERFACE)
END_ENUMERATION()
BEGIN_ENUMERATION(UserType::Aggregate)
	ENUMERATOR(UserType::Aggregate, NONE)
	ENUMERATOR(UserType::Aggregate, HOMOG_FLOAT)
	ENUMERATOR(UserType::Aggregate, HOMOG_DOUBLE)
END_ENUMERATION()
BEGIN_ENUMERATION(Pointer::Kind)
	ENUMERATOR(Pointer::Kind, PTR)
	ENUMERATOR(Pointer::Kind, L_REF)
	ENUMERATOR(Pointer::Kind, R_REF)
	ENUMERATOR(Pointer::Kind, WINRT_HAT)
END_ENUMERATION()
BEGIN_ENUMERATION(Pointer::Inheritance)
	ENUMERATOR(Pointer::Inheritance, NONE)
	ENUMERATOR(Pointer::Inheritance, SINGLE)
	ENUMERATOR(Pointer::Inheritance, MULTIPLE)
END_ENUMERATION()

BEGIN_ENUMERATION(Pointer::MemberType)
	ENUMERATOR(Pointer::MemberType, NONE)
	ENUMERATOR(Pointer::MemberType, DATA)
	ENUMERATOR(Pointer::MemberType, FUNCTION)
END_ENUMERATION()

BEGIN_ENUMERATION(Function::Virtuality)
	ENUMERATOR(Function::Virtuality, INTRO)
	ENUMERATOR(Function::Virtuality, OVERRIDE)
	ENUMERATOR(Function::Virtuality, NONE)
END_ENUMERATION()
BEGIN_ENUMERATION(Access)
	ENUMERATOR(Access, NONE)
	ENUMERATOR(Access, PRIVATE)
	ENUMERATOR(Access, PUBLIC)
	ENUMERATOR(Access, PROTECTED)
END_ENUMERATION()
BEGIN_ENUMERATION(CPU)
	ENUMERATOR(CPU, I8080)
	ENUMERATOR(CPU, I8086)
	ENUMERATOR(CPU, I80286)
	ENUMERATOR(CPU, I80386)
	ENUMERATOR(CPU, I80486)
	ENUMERATOR(CPU, PENTIUM)
	ENUMERATOR(CPU, PENTIUMII)
	ENUMERATOR(CPU, PENTIUMIII)
	ENUMERATOR(CPU, MIPS)
	ENUMERATOR(CPU, MIPS16)
	ENUMERATOR(CPU, MIPS32)
	ENUMERATOR(CPU, MIPS64)
	ENUMERATOR(CPU, MIPSI)
	ENUMERATOR(CPU, MIPSII)
	ENUMERATOR(CPU, MIPSIII)
	ENUMERATOR(CPU, MIPSIV)
	ENUMERATOR(CPU, MIPSV)
	ENUMERATOR(CPU, M68000)
	ENUMERATOR(CPU, M68010)
	ENUMERATOR(CPU, M68020)
	ENUMERATOR(CPU, M68030)
	ENUMERATOR(CPU, M68040)
	ENUMERATOR(CPU, ALPHA_21064)
	ENUMERATOR(CPU, ALPHA_21164)
	ENUMERATOR(CPU, ALPHA_21164A)
	ENUMERATOR(CPU, ALPHA_21264)
	ENUMERATOR(CPU, ALPHA_21364)
	ENUMERATOR(CPU, PPC601)
	ENUMERATOR(CPU, PPC603)
	ENUMERATOR(CPU, PPC604)
	ENUMERATOR(CPU, PPC620)
	ENUMERATOR(CPU, PPCFP)
	ENUMERATOR(CPU, PPCBE)
	ENUMERATOR(CPU, SH3)
	ENUMERATOR(CPU, SH3E)
	ENUMERATOR(CPU, SH3DSP)
	ENUMERATOR(CPU, SH4)
	ENUMERATOR(CPU, SHMEDIA)
	ENUMERATOR(CPU, ARM3)
	ENUMERATOR(CPU, ARM4)
	ENUMERATOR(CPU, ARM4T)
	ENUMERATOR(CPU, ARM5)
	ENUMERATOR(CPU, ARM5T)
	ENUMERATOR(CPU, ARM6)
	ENUMERATOR(CPU, ARM_XMAC)
	ENUMERATOR(CPU, ARM_WMMX)
	ENUMERATOR(CPU, ARM7)
	ENUMERATOR(CPU, OMNI)
	ENUMERATOR(CPU, IA64_1)
	ENUMERATOR(CPU, IA64_2)
	ENUMERATOR(CPU, CEE)
	ENUMERATOR(CPU, AM33)
	ENUMERATOR(CPU, M32R)
	ENUMERATOR(CPU, TRICORE)
	ENUMERATOR(CPU, X64)
	ENUMERATOR(CPU, EBC)
	ENUMERATOR(CPU, THUMB)
	ENUMERATOR(CPU, ARMNT)
	ENUMERATOR(CPU, ARM64)
	ENUMERATOR(CPU, D3D11_SHADER)
END_ENUMERATION()
BEGIN_ENUMERATION(Location)
	ENUMERATOR(Location, NONE)
	ENUMERATOR(Location, STATIC)
	ENUMERATOR(Location, TLS)
	ENUMERATOR(Location, REGREL)
	ENUMERATOR(Location, THISREL)
	ENUMERATOR(Location, ENREGISTERED)
	ENUMERATOR(Location, BITFIELD)
	ENUMERATOR(Location, SLOT)
	ENUMERATOR(Location, ILREL)
	ENUMERATOR(Location, METADATA)
	ENUMERATOR(Location, CONSTANT)
END_ENUMERATION()

#undef BEGIN_STRUCT
#undef UNIQUE_MEMBER
#undef MEMBER
#undef END_STRUCT
#undef BEGIN_ENUMERATION
#undef END_ENUMERATION
#undef ENUMERATOR