#pragma once

#include <stdint.h>

/* == Base Type == */
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

struct string8;

/* == Macros == */
#if _MSC_VER 
	#define COMPILER_MSVC
#elif __clang__
	#define COMPILER_CLANG
#else
	#error "Compiler not supported"
#endif

#pragma section(".roglob", read)
#define read_only __declspec(allocate(".roglob"))

#define array_len(arr) (sizeof(arr) / sizeof(*arr))

#ifndef _DEBUG
	#define Break()
	#define Assert(Expr)
#else
	#ifdef PLATFORM_WIN32
		#define Break() __debugbreak()
		#define Assert(Expr) if(!(Expr)) Break()
	#else
		#error "Debug macros are undefined on this platform"
	#endif
#endif

#if defined(COMPILER_CLANG)
	#define force_inline __attribute__((always_inline)) inline
#elif defined(COMPILER_MSVC)
	#define force_inline __forceinline
#endif

// #define SIMD_WIDTH 4 // Most modern CPUs have at least a width of 4
#ifndef SIMD_WIDTH
	#define SIMD_WIDTH 4
	#if defined(__AVX2__)
		#undef SIMD_WIDTH
		#define SIMD_WIDTH 8
	#endif
#endif

void DebugOutput(const string8 &String);

/* == Math == */

static constexpr f32 F32Epsilon = 1e-5f;
static constexpr f32 F32Min = 1e-30f;
static constexpr f32 F32Max = 1e30f;
static constexpr f32 PI32 = 3.14159265358979323846f;
static constexpr u32 SignBit = 0x8000'0000;

#ifndef _DEBUG
	#ifdef PLATFORM_WIN32
		#define MATHCALL static force_inline __vectorcall
	#else
		#define MATHCALL static force_inline
	#endif
#else
	#define MATHCALL static
#endif

#ifdef PLATFORM_X64
	#include <immintrin.h>
#endif

struct u32x2;
struct u32x3;
struct u32x4;
struct v2;
struct v3;
struct v4;
struct v8;
struct u128;

#include "basic_vector_types.h"

#if defined(PLATFORM_X64)
	union xmm {
		v4 V4;
		u32x4 U32x4;
		__m128 m128;
		__m128i m128i;

		force_inline constexpr xmm(f32 a) : V4(0.0f) { V4.x = a; } // movss
		force_inline constexpr xmm(u32 a) : U32x4((u32)0) { U32x4.x = a; }
		force_inline constexpr xmm(v2 a) : V4(a) { } // movsd
		force_inline constexpr xmm(v3 a) : V4(a) { }
		force_inline constexpr xmm(v4 a) : V4(a) { }
		force_inline constexpr xmm(__m128 a) : m128(a) { }
		force_inline constexpr xmm(__m128i a) : m128i(a) { }
		force_inline constexpr xmm(const u32x2 &a) : U32x4(a) { }
		force_inline constexpr xmm(const u32x3 &a) : U32x4(a) { }
		force_inline constexpr xmm(const u32x4 &a) : U32x4(a) { }

		force_inline explicit operator f32() const { return V4.x; }
		force_inline explicit operator v2() const { return { V4.x, V4.y }; }
		force_inline explicit operator v3() const { return { V4.x, V4.y, V4.z }; }
		force_inline explicit operator v4() const { return V4; }

		force_inline explicit operator u32() const { return U32x4.x; }
		force_inline explicit operator u32x2() const { return { U32x4.x, U32x4.y }; }
		force_inline explicit operator u32x3() const { return { U32x4.x, U32x4.y, U32x4.z }; }
		force_inline explicit operator u32x4() const { return U32x4; }

		force_inline operator __m128() const { return m128; }
		force_inline operator __m128i() const { return m128i; }
	};

	#if SIMD_WIDTH == 8
		union ymm {
			v8 V8;
			u32x8 U32x8;
			__m256 m256;
			__m256i m256i;

			force_inline constexpr ymm(f32 a) : V8(0.0f) { V8.x = a; } // movss
			force_inline constexpr ymm(u32 a) : U32x8((u32)0) { U32x8.x = a; }
			force_inline constexpr ymm(v8 a) : V8(a) { }
			force_inline constexpr ymm(u32x8 a) : U32x8(a) { }
			force_inline constexpr ymm(__m256 a) : m256(a) { }
			force_inline constexpr ymm(__m256i a) : m256i(a) { }
			force_inline explicit operator v8() const { return V8; }
			force_inline explicit operator u32x8() const { return U32x8; }
			force_inline operator __m256() const { return m256; }
			force_inline operator __m256i() const { return m256i; }
		};
	#endif

	#include "x64_operators.h"
#else
	#include "operators.h"
#endif

MATHCALL s32 s32_abs(s32 a);
MATHCALL s64 s64_abs(s64 a);
MATHCALL u32 u32_min(u32 a, u32 b);
MATHCALL u64 u64_min(u64 a, u64 b);
MATHCALL s32 s32_min(s32 a, s32 b);
MATHCALL s64 s64_min(s64 a, s64 b);
MATHCALL u32 u32_max(u32 a, u32 b);
MATHCALL u64 u64_max(u64 a, u64 b);
MATHCALL s32 s32_max(s32 a, s32 b);
MATHCALL s64 s64_max(s64 a, s64 b);

MATHCALL u32 u32_roundup_pw2(u32 a, u32 pw2);
MATHCALL u64 u64_roundup_pw2(u64 a, u64 pw2);

MATHCALL u32 u32_popcnt(u32 a);
MATHCALL u64 u64_popcnt(u32 a);

MATHCALL f32 f32_round(f32 a);
MATHCALL f32 f32_ceil(f32 a);
MATHCALL f32 f32_floor(f32 a);
MATHCALL f32 f32_sqrt(f32 a);
MATHCALL f32 f32_inv_sqrt(f32 a);
MATHCALL f32 f32_max(f32 a, f32 b);
MATHCALL f32 f32_min(f32 a, f32 b);
MATHCALL f32 f32_lerp(f32 a, f32 b, f32 t);
MATHCALL f32 f32_square(f32 a);
MATHCALL f32 f32_negate(f32 a);
MATHCALL f32 f32_sign(f32 a);
MATHCALL f32 f32_abs(f32 a);
MATHCALL f32 f32_mod(f32 a, f32 b);
MATHCALL f32 f32_clamp(f32 a, f32 Min, f32 Max);
MATHCALL f32 f32_madd(f32 a, f32 b, f32 c);

MATHCALL f32 f32_radians(f32 Degrees);
MATHCALL f32 f32_sin(f32 Radians);
MATHCALL f32 f32_cos(f32 Radians);
MATHCALL f32 f32_tan(f32 Radians);

MATHCALL f32 v2_dot(const v2 &a, const v2 &b);
MATHCALL f32 v3_dot(const v3 &a, const v3 &b);
MATHCALL f32 v4_dot(const v4 &a, const v4 &b);
MATHCALL f32 v2_length_sq(const v2 &a);
MATHCALL f32 v3_length_sq(const v3 &a);
MATHCALL f32 v4_length_sq(const v4 &a);
MATHCALL f32 v2_length(const v2 &a);
MATHCALL f32 v3_length(const v3 &a);
MATHCALL f32 v4_length(const v4 &a);
MATHCALL v2 v2_normalize(const v2 &a);
MATHCALL v3 v3_normalize(const v3 &a);
MATHCALL v4 v4_normalize(const v4 &a);
MATHCALL v3 v3_cross(const v3 &a, const v3 &b);

MATHCALL v2 v2_lerp(const v2 &a, const v2 &b, f32 t);
MATHCALL v3 v3_lerp(const v3 &a, const v3 &b, f32 t);
MATHCALL v4 v4_lerp(const v4 &a, const v4 &b, f32 t);

MATHCALL bool IsZeroed(const u32x2 &a);
MATHCALL bool IsZeroed(const u32x3 &a);
MATHCALL bool IsZeroed(const u32x4 &a);

#if defined(PLATFORM_X64)
	#include "x64_math.h"
#else
	#include "math.h"
#endif

/* Large Numbers */

/* == SIMD Helpers == */

struct u32x;
struct f32x;
struct v2x;
struct v3x;
struct v4x;

MATHCALL f32x operator+(const f32x &a, const f32x &b);
MATHCALL v2x operator+(const v2x &a, const v2x &b);
MATHCALL v3x operator+(const v3x &a, const v3x &b);
MATHCALL v4x operator+(const v4x &a, const v4x &b);
MATHCALL u32x operator+(const u32x &a, const u32x &b);

MATHCALL f32x operator-(const f32x &a, const f32x &b);
MATHCALL v2x operator-(const v2x &a, const v2x &b);
MATHCALL v3x operator-(const v3x &a, const v3x &b);
MATHCALL v4x operator-(const v4x &a, const v4x &b);
MATHCALL u32x operator-(const u32x &a, const u32x &b);

MATHCALL f32x operator*(const f32x &a, const f32x &b);
MATHCALL v2x operator*(const v2x &a, const v2x &b);
MATHCALL v3x operator*(const v3x &a, const v3x &b);
MATHCALL v4x operator*(const v4x &a, const v4x &b);
MATHCALL u32x operator*(const u32x &a, const u32x &b);

MATHCALL f32x operator/(const f32x &a, const f32x &b);
MATHCALL v2x operator/(const v2x &a, const v2x &b);
MATHCALL v3x operator/(const v3x &a, const v3x &b);
MATHCALL v4x operator/(const v4x &a, const v4x &b);
MATHCALL u32x operator/(const u32x &a, const u32x &b);

MATHCALL f32x operator-(const f32x &a);
MATHCALL v2x operator-(const v2x &a);
MATHCALL v3x operator-(const v3x &a);
MATHCALL v4x operator-(const v4x &a);
MATHCALL u32x operator-(const u32x &a);

MATHCALL u32x operator==(const f32x &a, const f32x &b);
MATHCALL u32x operator==(const v2x &a, const v2x &b);
MATHCALL u32x operator==(const v3x &a, const v3x &b);
MATHCALL u32x operator==(const v4x &a, const v4x &b);
MATHCALL u32x operator==(const u32x &a, const u32x &b);

MATHCALL u32x operator!=(const f32x &a, const f32x &b);
MATHCALL u32x operator!=(const v2x &a, const v2x &b);
MATHCALL u32x operator!=(const v3x &a, const v3x &b);
MATHCALL u32x operator!=(const v4x &a, const v4x &b);
MATHCALL u32x operator!=(const u32x &a, const u32x &b);

MATHCALL u32x operator>(const f32x &a, const f32x &b);
MATHCALL u32x operator>(const u32x &a, const u32x &b);

MATHCALL u32x operator<(const f32x &a, const f32x &b);
MATHCALL u32x operator<(const u32x &a, const u32x &b);

MATHCALL f32x operator&(const f32x &a, const u32x &b);
MATHCALL v2x operator&(const v2x &a, const u32x &b);
MATHCALL v3x operator&(const v3x &a, const u32x &b);
MATHCALL v4x operator&(const v4x &a, const u32x &b);
MATHCALL u32x operator&(const u32x &a, const u32x &b);

MATHCALL f32x operator|(const f32x &a, const u32x &b);
MATHCALL v2x operator|(const v2x &a, const u32x &b);
MATHCALL v3x operator|(const v3x &a, const u32x &b);
MATHCALL v4x operator|(const v4x &a, const u32x &b);
MATHCALL u32x operator|(const u32x &a, const u32x &b);

MATHCALL f32x operator^(const f32x &a, const u32x &b);
MATHCALL v2x operator^(const v2x &a, const u32x &b);
MATHCALL v3x operator^(const v3x &a, const u32x &b);
MATHCALL v4x operator^(const v4x &a, const u32x &b);
MATHCALL u32x operator^(const u32x &a, const u32x &b);

MATHCALL f32x operator~(const f32x &a);
MATHCALL v2x operator~(const v2x &a);
MATHCALL v3x operator~(const v3x &a);
MATHCALL v4x operator~(const v4x &a);
MATHCALL u32x operator~(const u32x &a);

MATHCALL f32x operator<<(const f32x &a, const u32 b);
MATHCALL v2x operator<<(const v2x &a, const u32 b);
MATHCALL v3x operator<<(const v3x &a, const u32 b);
MATHCALL v4x operator<<(const v4x &a, const u32 b);
MATHCALL u32x operator<<(const u32x &a, const u32 b);

MATHCALL f32x operator>>(const f32x &a, const u32x &b);
MATHCALL v2x operator>>(const v2x &a, const u32x &b);
MATHCALL v3x operator>>(const v3x &a, const u32x &b);
MATHCALL v4x operator>>(const v4x &a, const u32x &b);
MATHCALL u32x operator>>(const u32x &a, const u32x &b);

#if SIMD_WIDTH == 1
	#include "simd_helpers_scalar.h"
#elif SIMD_WIDTH == 4
	#include "simd_helpers_4x.h"
#elif SIMD_WIDTH == 8
	#include "simd_helpers_8x.h"
#else
	#error "SIMD Width Not Supported"
#endif

#include "simd_helpers_common.h"

MATHCALL u128 operator&(const u128 &a, const u128 &b);
MATHCALL u128 operator^(const u128 &a, const u128 &b);
MATHCALL u128 operator|(const u128 &a, const u128 &b);
MATHCALL u128 operator~(u128 a);
MATHCALL u128 SetBit(const u128 &a, u32 Bit);
MATHCALL u128 ClearBit(const u128 &a, u32 Bit);

#if defined(PLATFORM_X64)
	#include "x64_wide_math.h"
#else
	#include "wide_math.h"
#endif

MATHCALL u128 operator&=(u128 &a, const u128 &b) { return a = a & b; }
MATHCALL u128 operator^=(u128 &a, const u128 &b) { return a = a ^ b; }
MATHCALL u128 operator|=(u128 &a, const u128 &b) { return a = a | b; }

MATHCALL u128 SetBit(const u128 &a, u32 Bit) {
	Assert(Bit < 128);
	u128 Result = a;

	u32 Index = Bit / 32;
	u32 BitShift = Bit % 32 - 1;
	u32 BitToSet = 1 << (BitShift);

	u32 *Values = (u32 *)&Result.Value;
	Values[Index] |= BitToSet;

	return Result;
}
MATHCALL u128 ClearBit(const u128 &a, u32 Bit) {
	Assert(Bit < 128);
	u128 Result = a;

	u32 Index = Bit / 32;
	u32 BitShift = Bit % 32 - 1;
	u32 BitToClear = 1 << (BitShift);

	u32 *Values = (u32 *)&Result.Value;
	Values[Index] &= ~BitToClear;

	return Result;
}

/* == Psuedo Randomness == */
struct random_state64 {
	u64 Seed;
};
struct random_state128 {
	u128 Seed;
};

MATHCALL f32 f32_random(random_state64 *random_state);
MATHCALL f32 f32_random(random_state64 *random_state, f32 min, f32 max);
MATHCALL f32 f32_random(random_state128 *random_state);

MATHCALL u32 u32_random_pcg(random_state64 *random_state);
MATHCALL u32 u32_random_pcg(random_state128 *random_state);
MATHCALL u32 u32_random_lcg(random_state64 *random_state);
MATHCALL u32 u32_random_lcg(random_state128 *random_state);
MATHCALL u32 u32_random_xorshift(random_state64 *random_state);
MATHCALL u32 u32_random_xorshift(random_state128 *random_state);

#define RANDOM_ALGORITHM_PCG 1
#define RANDOM_ALGORITHM_LCG 2
#define RANDOM_ALGORITHM_XORSHIFT 3

#ifndef RANDOM_ALGORITHM
	#define RANDOM_ALGORITHM RANDOM_ALGORITHM_PCG
#endif

#if RANDOM_ALGORITHM == RANDOM_ALGORITHM_PCG
	#define u32_random u32_random_pcg
#elif RANDOM_ALGORITHM == RANDOM_ALGORITHM_PCG
	#define u32_random u32_random_lcg
#elif
	#define u32_random u32_random_xorshift
#endif

/* == Error Handling == */

struct err { };
void ErrorAccumulationBegin();
void ErrorAccumulationEnd();

/* == Profiling / Timing == */
u64 TimerSample();
f64 TimestampToSeconds(u64 *Time);

/* == Memory == */

#define KB(b) (b * 1024)
#define MB(b) (KB(b) * 1024)
#define GB(b) (MB(b) * 1024LLU)
#define TB(b) (GB(b) * 1024LLU)

void ZeroMemory(void *Ptr, u64 Size);

struct memory_arena {
	void *Start;
	void *Offset;
	u32 Size;
};

extern memory_arena TempArena;

// Reserve and commit all memory up front
void ArenaInit(memory_arena *Arena, u64 Size, u64 StartingAddress);
void *ArenaPush(memory_arena *Arena, u64 Size);
void *ArenaPushAligned(memory_arena *Arena, u64 Size, u32 Alignment);
void ArenaPop(memory_arena *Arena, void *Ptr);

// thread_local temp storage
void *Push(u64 Size);
void *PushAligned(u64 Size, u32 Alignment);
void Pop(void *Ptr);

// Reserve large amount of memory and commit only as necessary
// void ArenaReserve(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, u64 StartingAddress);
// void *PushAndCommit(memory_arena *Arena, u64 Size, u64 Count);
// void *PushAndCommitAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment);
// void PopAndDecommit(memory_arena *Arena, void *Ptr);

// Use a linked list of virtual memory pages
// void ArenaInitChained(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, u64 StartingAddress);
// void *PushChained(memory_arena *Arena, u64 Size, u64 Count);
// void *PushChainedAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment);
// void PopChained(memory_arena *Arena, void *Ptr);

struct deferred_pop {
	memory_arena *Arena;
	void *Ptr;
	inline deferred_pop(memory_arena *Arena) {
		this->Arena = Arena;
		this->Ptr = Arena->Offset;
	}
	inline deferred_pop() {
		this->Arena = &TempArena;
		this->Ptr = TempArena.Offset;
	}

	inline ~deferred_pop() {
		ArenaPop(Arena, Ptr);
	}
};
#define DeferredPop(Arena) deferred_pop dp_ = deferred_pop(Arena);

// struct chained_arena

/* == Strings == */
typedef char char8;

struct string8 {
	char8 *Data;
	u32 Length;

	constexpr string8(const char8 *Str) : Data(const_cast<char8 *>(Str)), Length(0) {
		u32 Length = 0;
		char8 *S = const_cast<char8 *>(Str);
		while (*Str) {
			char8 C = *S;

#if 0
			u32 CodepointLength = 1 + ((C & 0xE0) == 0xC0) + ((C & 0xF0) == 0xD) + ((C & 0xF8) == 0xF0);
			Str += CodepointLength;
#else
			Str += 1;
#endif
			Length += 1;
		}
		this->Length = Length;
	}
	constexpr string8(const char8 *Str, u32 Length) : Data(const_cast<char8 *>(Str)), Length(Length) { }
};

static inline wchar_t *ConvertUTF8toUTF16(memory_arena *Arena, const string8 &String);

constexpr u64 StringHash(const string8 &String);

/* == File / IO == */

/* == Threading == */
// thread_local storage
// work queue

/* == Assets == */

/* == Windowing / Input == */
void CreateWindow(const string8 &Title, u32 Width, u32 Height);
void ResizeWindow(u32 Width, u32 Height);
bool ShouldWindowClose();
s32 AppMain(void);

enum class key : u32 {
    Escape = 0x1,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Zero,
	Minus,
	Plus,
	Backspace,
	Tab,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	LeftBracket,
	RightBracket,
	Enter,
	LeftControl,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Semicolon,
	Quote,
	GraveAccent,
	LeftShift,
	Pipe,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	Comma,
	Period,
	QuestionMark,
	RightShift,
	NumpadMultiply,
	LeftAlt,
	Space,
	CapsLock,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	Pause,
	ScrollLock,
	Numpad7,
	Numpad8,
	Numpad9,
	NumpadMinus,
	Numpad4,
	Numpad5,
	Numpad6,
	NumpadPlus,
	Numpad1,
	Numpad2,
	Numpad3,
	Numpad0,
	NumpadPeriod,
	AltPrintScreen,
	_Unused,
	OEM10,
	F11,
	F12,
	LeftWindows,
	RightAlt,
	RightWindows,
	Menu,
	RightControl,
	Insert,
	Home,
	PageUp,
	Delete,
	End,
	PageDown,
	ArrowUp,
	ArrowLeft,
	ArrowDown,
	ArrowRight,
	NumLock,
	NumpadForwardSlash,
	NumpadEnter,
	Count
};

bool IsButtonDown(key Key);
bool IsButtonUp(key Key);
bool WasButtonReleased(key Key);
bool WasButtonPressed(key Key);

enum class button : u32 {
	DPadUp         = 0,
	DPadDown       = 1,
	DPadLeft       = 2,
	DPadRight      = 3,
	Start          = 4,
	Back           = 5,
	LeftThumb      = 6,
	RightThumb     = 7,
	LeftShoulder   = 8,
	RightShoulder  = 9,
	A              = 10,
	B              = 11,
	X              = 12,
	Y              = 13,
	Count
};
bool IsButtonDown(button Button);
bool IsButtonUp(button Button);
bool WasButtonReleased(button Button);
bool WasButtonPressed(button Button);
v2 GetAnalogInput();

enum class mouse_button : u32 {
	LeftMouseButton   = 1 << 0,
	RightMouseButton  = 1 << 1,
	MiddleMouseButton = 1 << 2,
	XButton1          = 1 << 3,
	XButton2          = 1 << 4,
	Count
};

v2 GetMouseDelta();
s32 GetMouseWheelDelta();
bool IsButtonDown(mouse_button Button);
bool IsButtonUp(mouse_button Button);
bool WasButtonReleased(mouse_button Button);
bool WasButtonPressed(mouse_button Button);

/* == Graphics == */

struct m2 {
	v2 X;
	v2 Y;

	inline constexpr v2 &operator[](u32 Index) {
		Assert(Index < 2);
		if (Index == 0) return X;
		return Y;
	}

	constexpr MATHCALL m2 Identity() {
		m2 Result = {0};
		Result[0][0] = 1.0f;
		Result[1][1] = 1.0f;
		return Result;
	}
};

enum class format : u32 {
	R32B32G32A32_F32 = 0x1,
	R8B8G8A8_U32
};

struct image {
	void *Data;
	u32 Width, Height;
	format Format;
};

void ClearBackground(v3 Color);
image CreateImage(memory_arena *Arena, u32 Width, u32 Height, format Format);

u32 CreateTextureFromImage(image Image);
void BlitTexture(u32 Texture);
void DeleteTexture(u32 Texture);

void PushMatrix(m2 Matrix);
void PopMatrix();

void Draw();

/* == Sound == */

struct SoundHandle {
	u32 H;
	force_inline explicit operator u32() const { return H; }
};

void InitSoundEngine();
SoundHandle PlaySound(u64 Hash);
void StopSound(SoundHandle Handle);
