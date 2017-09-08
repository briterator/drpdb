#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <functional>
#undef VOID
#undef INTERFACE
#undef PASCAL

struct IDiaSymbol;
struct IDiaLineNumber;
struct IDiaSourceFile;
struct IDiaInjectedSource;
struct IDiaSectionContrib;
struct IDiaSession;
struct IDiaFrameData;

namespace Sym
{
	enum class TableType
	{
		Master,
		Data,
		Function,
		Files
	};
	struct address_info
	{
		uint32_t rv;
		template<class T>
		void init(T*);
	};
	//must match CV_CPU_TYPE_e
	enum class CPU
	{
		I8080 = 0x00,
		I8086 = 0x01,
		I80286 = 0x02,
		I80386 = 0x03,
		I80486 = 0x04,
		PENTIUM = 0x05,
		PENTIUMII = 0x06,
		PENTIUMIII = 0x07,
		MIPS = 0x10,
		MIPS16 = 0x11,
		MIPS32 = 0x12,
		MIPS64 = 0x13,
		MIPSI = 0x14,
		MIPSII = 0x15,
		MIPSIII = 0x16,
		MIPSIV = 0x17,
		MIPSV = 0x18,
		M68000 = 0x20,
		M68010 = 0x21,
		M68020 = 0x22,
		M68030 = 0x23,
		M68040 = 0x24,
		ALPHA_21064 = 0x30,
		ALPHA_21164 = 0x31,
		ALPHA_21164A = 0x32,
		ALPHA_21264 = 0x33,
		ALPHA_21364 = 0x34,
		PPC601 = 0x40,
		PPC603 = 0x41,
		PPC604 = 0x42,
		PPC620 = 0x43,
		PPCFP = 0x44,
		PPCBE = 0x45,
		SH3 = 0x50,
		SH3E = 0x51,
		SH3DSP = 0x52,
		SH4 = 0x53,
		SHMEDIA = 0x54,
		ARM3 = 0x60,
		ARM4 = 0x61,
		ARM4T = 0x62,
		ARM5 = 0x63,
		ARM5T = 0x64,
		ARM6 = 0x65,
		ARM_XMAC = 0x66,
		ARM_WMMX = 0x67,
		ARM7 = 0x68,
		OMNI = 0x70,
		IA64_1 = 0x80,
		IA64_2 = 0x81,
		CEE = 0x90,
		AM33 = 0xA0,
		M32R = 0xB0,
		TRICORE = 0xC0,
		X64 = 0xD0,
		EBC = 0xE0,
		THUMB = 0xF0,
		ARMNT = 0xF4,
		ARM64 = 0xF6,
		D3D11_SHADER = 0x100,
	};
	//must match LocationType enum
	enum class Location : uint8_t
	{
		NONE,
		STATIC,
		TLS,
		REGREL,
		THISREL,
		ENREGISTERED,
		BITFIELD,
		SLOT,
		ILREL,
		METADATA,
		CONSTANT
	};
	//must match CV_CFL_LANG
	enum class Language : uint8_t
	{
		C,
		CXX,
		FORTRAN,
		MASM,
		PASCAL,
		BASIC,
		COBOL,
		LINK,
		CVTRES,
		CVTPGD,
		CSHARP,
		VB,
		ILASM,
		JAVA,
		JS,
		CIL,
		HLSL
	};

	//must match SymTagEnum
	enum class Tag : uint8_t
	{
		Unknown,
		Exe,
		Compiland,
		CompilandDetails,
		CompilandEnv,
		Function,
		Block,
		Data,
		Annotation,
		Label,
		PublicSymbol,
		UDT,
		Enum,
		FunctionType,
		PointerType,
		ArrayType,
		BaseType,
		Typedef,
		BaseClass,
		Friend,
		FunctionArgType,
		FuncDebugStart,
		FuncDebugEnd,
		UsingNamespace,
		VTableShape,
		VTable,
		Custom,
		Thunk,
		CustomType,
		ManagedType,
		Dimension,
		CallSite,
		InlineSite,
		BaseInterface,
		VectorType,
		MatrixType,
		HLSLType,
		Caller,
		Callee,
		Export,
		HeapAllocationSite,
		CoffGroup,
		Max
	};
	//must match CV_access_e
	enum class Access : uint8_t
	{
		NONE = 0,
		PRIVATE = 1,
		PROTECTED = 2,
		PUBLIC = 3
	};
	struct InputAssembly
	{
		std::string filename;
		uint32_t index_;
		uint32_t timestamp;
		uint32_t uid;
		bool pdb_available_at_il_merge : 1;
		InputAssembly()  noexcept {}
		InputAssembly(struct IDiaInputAssemblyFile*)  noexcept;
	};
	struct SectionContrib
	{
		address_info address;
		uint32_t compiland_symbol;
		uint32_t data_crc;
		uint32_t length;
		uint32_t relocations_crc;
		bool code : 1;
		bool code_16bit : 1;
		bool comdat : 1;
		bool executable : 1;
		bool discardable : 1;
		bool initialized_data : 1;
		bool uninitialized_data : 1;
		bool cached : 1;
		bool paged : 1;
		bool readable : 1;
		bool writeable : 1;
		bool remove : 1;
		bool share : 1;
		SectionContrib()  noexcept {}
		SectionContrib(IDiaSectionContrib*)  noexcept;
	};
	struct Frame
	{
		std::string program;
		address_info address;
		uint32_t length_block;
		uint32_t length_locals;
		uint32_t length_params;
		uint32_t max_stack;
		uint32_t length_prolog;
		uint32_t length_saved_registers;
		uint32_t type_symbol;

		bool exceptions_system : 1;
		bool exceptions_cxx : 1;
		bool function_start : 1;
		bool allocate_base_pointer : 1;

		Frame() noexcept {}
		Frame(IDiaFrameData*)  noexcept;
	};
	struct Segment
	{
		uint32_t address_section;
		uint32_t address_rv;
		uint32_t frame;
		uint32_t length;
		uint32_t offset;
		bool executable : 1;
		bool readable : 1;
		bool writable : 1;

		Segment()  noexcept {}
		Segment(struct IDiaSegment*)  noexcept;
	};
	struct Symbol
	{
		std::string name;
		unsigned long symbol;
		unsigned long lexical_parent_symbol;
		unsigned long parent_symbol;
		unsigned long long size;
		Tag tag;
		Location location_type;

		Symbol(IDiaSymbol*, unsigned long Id, unsigned char Tag)  noexcept;
		Symbol()  noexcept
		{
			symbol = 0;
			lexical_parent_symbol = 0;
			parent_symbol = 0;
			size = 0;
			tag = Tag::Unknown;
			location_type = Location::NONE;
		}
	};
	struct Inlined
	{
		uint32_t symbol;
		uint32_t type_symbol;
		address_info address;
		uint32_t pgo_edges;
		Inlined()  noexcept {}
		Inlined(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct PublicSymbol
	{
		enum Type : uint8_t
		{
			FUNCTION,
			DATA,
			OTHER
		};
		uint32_t symbol;
		address_info address;
		Type type;
		bool managed : 1;
		bool cil : 1;
		PublicSymbol()  noexcept {}
		PublicSymbol(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct Compiland
	{
		uint32_t symbol;
		std::string library;
		std::string compiler;
		uint32_t backend_build;
		uint32_t backend_major;
		uint32_t backend_minor;
		uint32_t frontend_build;
		uint32_t frontend_major;
		uint32_t frontend_minor;
		uint32_t frontend_qfe;
		uint32_t backend_qfe;
		Language language;
		CPU platform;
		bool sdl : 1;
		bool pgo : 1;
		bool security_check : 1;
		bool managed : 1;
		bool debug_info : 1;
		bool edit_and_continue : 1;
		bool ltcg : 1;
		bool data_aligned : 1;
		bool hotpatchable : 1;
		bool cvtcil : 1;
		bool cil_netmodule : 1;
		Compiland()  noexcept {}
		Compiland(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
		void AppendDetails(IDiaSymbol*);
	};
	struct CompilandEnv
	{
		uint32_t compiland_symbol;
		std::string option_name;
		std::string value;
		CompilandEnv()  noexcept {}
		CompilandEnv(IDiaSymbol*)  noexcept;
	};
	struct Exe
	{
		std::string guid;
		std::string symbols_path;
		uint32_t symbol;
		uint32_t age;
		bool ctypes : 1;
		bool stripped : 1;
		uint32_t architecture;
		uint32_t signature;

		Exe()  noexcept {}
		Exe(IDiaSymbol*) noexcept;
	};
	struct Block
	{
		uint32_t symbol;
		address_info address;
		Block()  noexcept {}
		Block(IDiaSymbol*, uint32_t symIndexId_) noexcept;
	};
	struct FunctionArg
	{
		uint32_t symbol;
		uint32_t type_symbol;
		FunctionArg()  noexcept {}
		FunctionArg(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};
	struct HeapAllocation
	{
		uint32_t symbol;
		address_info address;
		uint32_t type_symbol;
		HeapAllocation() noexcept {}
		HeapAllocation(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};
	struct Thunk
	{
		//must match THUNK_ORDINAL
		enum class Ordinal : uint8_t
		{
			NONE,
			THIS_ADJUSTOR,
			VIRTUAL_CALL,
			PCODE,
			DELAY_LOAD,
			TRAMPOLINE_INCREMENTAL,
			TRAMPOLINE_BRANCHISLAND,
		};
		Ordinal ordinal;
		uint32_t symbol;
		address_info address;
		address_info target;
		uint32_t target_symbol;
		Thunk()  noexcept {}
		Thunk(IDiaSession*, IDiaSymbol*, uint32_t symIndexId_) noexcept;
	};
	struct Data
	{
		//must match DataKind
		enum class Kind : uint8_t
		{
			UNKNOWN,
			LOCAL,
			STATICLOCAL,
			PARAM,
			OBJECTPTR,
			FILESTATIC,
			GLOBAL,
			MEMBER,
			STATICMEMBER,
			CONSTANT
		};
		unsigned long symbol;
		int64_t value;
		uint32_t type_symbol;
		uint32_t offset;
		address_info address;
		uint32_t register_id;
		uint32_t bit_position;
		Kind kind;
		bool const_export : 1;
		Data()  noexcept {}
		Data(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct Label
	{
		uint32_t symbol;
		address_info address;
		Label()  noexcept {}
		Label(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct Function
	{
		enum class Virtuality : uint8_t
		{
			INTRO,
			OVERRIDE,
			NONE
		};
		uint32_t symbol;
		uint32_t virtual_base_offset;
		uint32_t type_symbol;
		Sym::Access access;
		Virtuality virtuality;
		uint64_t pgo_dyn_instr_count;
		uint32_t static_size;
		uint32_t pbp_regid;
		uint32_t lbp_regid;
		uint32_t final_live_static_size;
		uint32_t frame_size;
		address_info address;
		address_info eh_address;
		uint32_t pgo_entry_count;
		bool control_flow_check : 1;
		bool alloca_ : 1;
		bool exceptions : 1;
		bool asm_ : 1;
		bool sealed : 1;
		bool security_checks : 1;
		bool inlined : 1;
		bool static_ : 1;
		bool noinline : 1;
		bool noreturn : 1;
		bool unreachable : 1;
		bool setjmp_ : 1;
		bool const_export : 1;
		bool strict_gs_check : 1;
		bool longjmp : 1;
		bool eh : 1;
		bool eha : 1;
		bool seh : 1;
		bool optimized_debug_info : 1;
		bool frame_pointer : 1;
		bool interrupt_return : 1;
		bool pure_virtual : 1;
		bool far_return : 1;
		bool naked : 1;
		bool inline_ : 1;
		bool custom_call : 1;
		bool stack_ordering : 1;
		bool safebuffers : 1;
		bool pgo : 1;
		bool has_pgo_counts : 1;
		bool optimized_for_speed : 1;
		bool compiler_generated : 1;

		Function()  noexcept {}
		Function(IDiaSymbol* sym, uint32_t symIndexId_)  noexcept;
	};
	struct VTablePtr
	{
		uint32_t symbol;
		uint32_t offset;
		uint32_t type_symbol;
		VTablePtr() noexcept {}
		VTablePtr(IDiaSymbol* sym, uint32_t symIndexId_) noexcept;

	};

	//my example pdbs never return a SymTagVTableShape...
	struct VTableShape
	{
		uint32_t symbol;
		uint32_t count;
		VTableShape() noexcept {}
		VTableShape(IDiaSymbol* sym, uint32_t symIndexId_) noexcept;
	};

	struct Friend
	{
		uint32_t symbol;
		uint32_t type_symbol;
		Friend() noexcept {}
		Friend(IDiaSymbol* sym, uint32_t symIndexId_) noexcept;
	};
	struct Export
	{
		uint32_t symbol;
		uint32_t address_offset;
		uint32_t rank;
		uint32_t ordinal;
		bool const_export : 1;
		bool data_export : 1;
		bool private_export : 1;
		bool noname : 1;
		bool explicit_ordinal : 1;
		bool forwarder : 1;

		bool function_ : 1;
		bool const_ : 1;
		Export()  noexcept {}
		Export(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};
	struct AddrSection
	{
		enum class Kind
		{
			UNKNOWN,
			DATA,
			BSS,
			CODE,
			READDATA
		};
		uint32_t section_index;
		uint32_t line_numbers;
		unsigned long size;
		unsigned long relocations;
		bool comdat : 1;
		bool executable : 1;
		bool readable : 1;
		bool writable : 1;
		bool discardable : 1;
		std::string name;
	};

	struct Included
	{
		uint32_t compiland_symbol;
		uint32_t source_id;
		Included()  noexcept {}
		Included(uint32_t compiland, uint32_t src)  noexcept
			:compiland_symbol(compiland)
			, source_id(src) {}
	};

	struct BuiltinType
	{
		//must match BasicType
		enum class Kind : uint8_t
		{
			NONE = 0,
			VOID = 1,
			CHAR = 2,
			WCHAR = 3,
			INT = 6,
			UINT = 7,
			FLOAT = 8,
			BCD = 9,
			BOOL = 10,
			LONG = 13,
			ULONG = 14,
			CURRENCY = 25,
			DATE = 26,
			VARIANT = 27,
			COMPLEX = 28,
			BIT = 29,
			BSTR = 30,
			HRESULT = 31,
			CHAR16 = 32,  // char16_t
			CHAR32 = 33,  // char32_t
		};
		uint32_t symbol;
		uint32_t array_index_type_symbol;
		uint32_t type_symbol;
		uint32_t count;
		Kind kind;
		bool unaligned : 1;
		bool const_ : 1;
		bool volatile_ : 1;
		bool const_export : 1;

		BuiltinType()  noexcept {}
		BuiltinType(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};
	struct UserType
	{
		//must match UDTKind
		enum class Kind : uint8_t
		{
			STRUCT,
			CLASS,
			UNION,
			INTERFACE
		};
		enum class Aggregate : uint8_t
		{
			NONE,
			HOMOG_FLOAT,
			HOMOG_DOUBLE
		};
		enum class Semantics : uint8_t
		{
			UNKNOWN,
			VALUE,
			REFERENCE,
			INTERFACE
		};
		uint32_t symbol;
		uint32_t src_line;
		uint32_t vtable_shape;
		uint32_t vtable_count;
		
		Kind kind;
		Aggregate aggregate_type;
		Semantics semantics;
		bool packed : 1;
		bool unaligned : 1;
		bool const_ : 1;
		bool volatile_ : 1;
		bool overloaded_operators : 1;
		bool nested : 1;
		bool has_nested_types : 1;
		bool assignment_operator : 1;
		bool cast_operator : 1;
		bool intrinsic : 1;
		bool scoped : 1;
		bool constructor : 1;
		UserType()  noexcept {}
		UserType(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct InjectedSource
	{
		uint64_t length;
		std::string text;
		InjectedSource()  noexcept {}
		InjectedSource(IDiaInjectedSource*)  noexcept;
	};
	struct Enum
	{
		uint32_t symbol;
		uint32_t unmodified_type_symbol;
		uint32_t type_symbol;
		BuiltinType::Kind type;
		bool packed : 1;
		bool scoped : 1;

		Enum()  noexcept {}
		Enum(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};
	struct SourceFile
	{
		uint32_t source_id;
		std::string path;
		SourceFile()  noexcept {}
		SourceFile(IDiaSourceFile*)  noexcept;
	};
	struct Pointer
	{
		enum class Kind : uint8_t
		{
			PTR,
			L_REF,
			R_REF,
			WINRT_HAT
		};
		enum class Inheritance : uint8_t
		{
			NONE,
			SINGLE,
			MULTIPLE
		};
		enum class MemberType : uint8_t
		{
			NONE,
			DATA,
			FUNCTION
		};
		uint32_t symbol;
		uint32_t type_symbol;
		uint32_t unmodified_type_symbol;
		Kind kind;
		Inheritance inheritance;
		MemberType member_type;
		bool unaligned : 1;
		bool const_ : 1;
		bool volatile_ : 1;
		bool restrict_ : 1;
		bool constant_export : 1;
		bool virtual_inheritance : 1;

		Pointer()  noexcept {}
		Pointer(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};


	struct FunctionType
	{
		//must match CV_call_e
		enum class CallConv : uint8_t
		{
			NEAR_C = 0x00, // near right to left push, caller pops stack
			FAR_C = 0x01, // far right to left push, caller pops stack
			NEAR_PASCAL = 0x02, // near left to right push, callee pops stack
			FAR_PASCAL = 0x03, // far left to right push, callee pops stack
			NEAR_FAST = 0x04, // near left to right push with regs, callee pops stack
			FAR_FAST = 0x05, // far left to right push with regs, callee pops stack
			SKIPPED = 0x06, // skipped (unused) call index
			NEAR_STD = 0x07, // near standard call
			FAR_STD = 0x08, // far standard call
			NEAR_SYS = 0x09, // near sys call
			FAR_SYS = 0x0a, // far sys call
			THISCALL = 0x0b, // this call (this passed in register)
			MIPSCALL = 0x0c, // Mips call
			GENERIC = 0x0d, // Generic call sequence
			ALPHACALL = 0x0e, // Alpha call
			PPCCALL = 0x0f, // PPC call
			SHCALL = 0x10, // Hitachi SuperH call
			ARMCALL = 0x11, // ARM call
			AM33CALL = 0x12, // AM33 call
			TRICALL = 0x13, // TriCore Call
			SH5CALL = 0x14, // Hitachi SuperH-5 call
			M32RCALL = 0x15, // M32R Call
			CLRCALL = 0x16, // clr call
			INLINE = 0x17, // Marker for routines always inlined and thus lacking a convention
			NEAR_VECTOR = 0x18, // near left to right push with regs, callee pops stack
			RESERVED = 0x19  // first unused call enumeration
		};
		uint32_t symbol;
		int32_t this_adjust;
		uint32_t param_count;
		uint32_t return_type_symbol;
		uint32_t this_type_symbol;
		bool is_constructor : 1;
		bool volatile_ : 1;
		bool const_ : 1;
		bool unaligned : 1;
		bool cxx_return_udt : 1;
		bool constructor_virtual_base : 1;
		bool constant_export : 1;
		CallConv call_convention;

		FunctionType()  noexcept {}
		FunctionType(IDiaSymbol*, uint32_t symIndexId_)  noexcept;
	};

	struct Callsite
	{
		uint32_t symbol;
		uint32_t target_symbol;
		address_info address;
		Callsite(IDiaSession* session, IDiaSymbol* diaSymbol, uint32_t symIndexId_)  noexcept;
		Callsite()  noexcept {}
	};

	struct BaseClass
	{
		uint32_t child_symbol;
		uint32_t parent_symbol;
		uint32_t offset;
		uint32_t vdisp_index;
		uint32_t vbase_type_symbol;
		uint32_t vbase_offset;
		bool virtual_;
		bool indirect_virtual;
		Sym::Access access;
		BaseClass()  noexcept {}
		BaseClass(IDiaSymbol*) noexcept;
	};
	struct Typedef
	{
		uint32_t symbol;
		uint32_t type_symbol;
		uint32_t unmodified_type_symbol;
		Typedef() noexcept {}
		Typedef(IDiaSymbol*, uint32_t symIndexId) noexcept;
	};
	struct Array
	{
		uint32_t symbol;
		uint32_t index_type_symbol;
		uint32_t count;
		uint32_t rank;
		uint32_t type_symbol;
		Array() noexcept {}
		Array(IDiaSymbol*, uint32_t symIndexId) noexcept;
	};

	struct SrcRange
	{
		uint32_t id;
		uint32_t compiland_symbol;
		uint32_t src_file;
		uint32_t line_begin;
		uint32_t line_end;
		uint32_t column_begin;
		uint32_t column_end;
		uint32_t address_section;
		uint32_t address_rv;
		uint32_t address_offset;
		uint32_t length;
		bool statement;
		SrcRange()  noexcept {}
		SrcRange(uint32_t id, IDiaLineNumber* line) noexcept;
	};
}

inline std::string wstrcvt(const wchar_t* s)
{
	std::string Result;
	if (s == nullptr)
		return Result;
	auto n = wcslen(s);
	Result.reserve(n);
	Result.insert(0, n, 0);
	auto d = Result.begin();
	for (auto i = 0; i < n; ++i)
	{
		d[i] = (char)s[i];
	}
	return Result;
}

struct SymbolData
{
	std::vector<Sym::Exe> Exe;
	std::vector<Sym::Thunk> Thunk;
	std::vector<Sym::Compiland> Compiland;
	std::vector<Sym::BuiltinType> BuiltinType;
	std::vector<Sym::Function> Function;
	std::vector<Sym::Symbol> Symbol;
	std::vector<Sym::UserType> UserType;
	std::vector<Sym::AddrSection> AddrSection;
	std::vector<Sym::Enum> Enum;
	std::vector<Sym::FunctionArg> FunctionArg;
	std::vector<Sym::FunctionType> FunctionType;
	std::vector<Sym::Data> Data;
	std::vector<Sym::Pointer> Pointer;
	std::vector<Sym::BaseClass> BaseClass;
	std::vector<Sym::Callsite> Callsite;
	std::vector<Sym::Typedef> Typedef;
	std::vector<Sym::SrcRange> SrcRange;
	std::vector<Sym::Array> Array;
	std::vector<Sym::InjectedSource> InjectedSource;
	std::vector<Sym::CompilandEnv> CompilandEnv;
	std::vector<Sym::SourceFile> SourceFile;
	std::vector<Sym::Label> Label;
	std::vector<Sym::PublicSymbol> PublicSymbol;
	std::vector<Sym::Included> Included;
	std::vector<Sym::Export> Export;
	std::vector<Sym::InputAssembly> InputAssembly;
	std::vector<Sym::Segment> Segment;
	std::vector<Sym::SectionContrib> SectionContrib;
	std::vector<Sym::HeapAllocation> HeapAllocation;
	std::vector<Sym::Block> Block;
	std::vector<Sym::Inlined> Inlined;
	std::vector<Sym::Frame> Frame;
	std::vector<Sym::VTablePtr> VTablePtr;
	std::vector<Sym::VTableShape> VTableShape;
	std::vector<Sym::Friend> Friend;

	template<class ELEMENT>
	struct emplace_helper
	{
		std::vector<ELEMENT>& contrib;
		emplace_helper(std::vector<ELEMENT>& in) : contrib(in) {}
		void init(uint64_t n) { contrib.reserve(n); }
		template<class T>
		void element(T&& item) { contrib.emplace_back(item); }
	};

	auto ReadSectionContrib()
	{
		return emplace_helper<Sym::SectionContrib>(SectionContrib);
	}
	auto ReadInjectedSource()
	{
		return emplace_helper<Sym::InjectedSource>(InjectedSource);
	}

	auto ReadSegment()
	{
		return emplace_helper<Sym::Segment>(Segment);
	}
	auto ReadInputAssembly()
	{
		return emplace_helper<Sym::InputAssembly>(InputAssembly);
	}
	auto ReadFrame()
	{
		return emplace_helper<Sym::Frame>(Frame);
	}

	SymbolData()
	{
		Symbol.reserve(120000);
		Typedef.reserve(2048);
		FunctionArg.reserve(16384);
		Data.reserve(16384);
		PublicSymbol.reserve(16384);
		Function.reserve(16384);
		UserType.reserve(16384);
		SourceFile.reserve(512);
		Compiland.reserve(512);
		BaseClass.reserve(16384);
	}
};

struct OutputEngine
{
	using OutputFn = void( SymbolData& );
	using DescribeFn = std::string();

	std::string name;
	OutputFn* output{ nullptr };
	DescribeFn* describe{ nullptr };
};

std::string getOption(const char* name);
bool getFlag(const char* name);
void set_error(const char* err);
bool has_error();