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

#define abs(a) ((a < 0) ? a * -1 : a)
#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

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

#if defined(PLATFORM_X64)
	#include "x64_math.h"
#else
	#include "math.h"
#endif

/* == SIMD Helpers == */

struct u32x;
struct f32x;
struct v2x;
struct v3x;
struct v4x;
struct u128;
struct u256;

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

#if SIMD_WIDTH == 4
	#include "simd_helpers_4x.h"
#elif SIMD_WIDTH == 8
	#include "simd_helpers_8x.h"
#else
	#error "SIMD Width Not Supported"
#endif

#include "simd_helpers_common.h"

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

// Reserve and commit all memory up front
void ArenaInitCommitAndReserve(memory_arena *Arena, u64 Size, u64 StartingAddress);
void *PushFast(memory_arena *Arena, u64 Size, u64 Count);
void *PushFastAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment);
void PopFast(memory_arena *Arena, void *Ptr);

// Reserve large amount of memory and commit only as necessary
void ArenaReserve(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, u64 StartingAddress);
void *PushAndCommit(memory_arena *Arena, u64 Size, u64 Count);
void *PushAndCommitAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment);
void PopAndDecommit(memory_arena *Arena, void *Ptr);

// Use a linked list of virtual memory pages
void ArenaInitChained(memory_arena *Arena, u64 ReserveSize, u64 CommitSize, u64 StartingAddress);
void *PushChained(memory_arena *Arena, u64 Size, u64 Count);
void *PushChainedAligned(memory_arena *Arena, u64 Size, u64 Count, u32 Alignment);
void PopChained(memory_arena *Arena, void *Ptr);

#define DEFAULT_MEM_ALLOC_STRATEGY_FAST 1
#define DEFAULT_MEM_ALLOC_STRATEGY_COMMIT_AS_NEEDED 2
#define DEFAULT_MEM_ALLOC_STRATEGY_CHAINED 3

#ifndef DEFAULT_MEM_ALLOC_STRATEGY
	#define DEFAULT_MEM_ALLOC_STRATEGY DEFAULT_MEM_ALLOC_STRATEGY_FAST
#endif

#if RANDOM_ALGORITHM == DEFAULT_MEM_ALLOC_STRATEGY_FAST
	#define Push PushFast
	#define Pop PopFast
#elif RANDOM_ALGORITHM == DEFAULT_MEM_ALLOC_STRATEGY_COMMIT_AS_NEEDED
	#define Push PushAndCommit
	#define Pop PopAndDecommit
#elif
	#define Push PushChained
	#define Pop PopChained
#endif

struct DeferredPop {
	memory_arena *Arena;
	void *Ptr;
	DeferredPop(memory_arena *Arena, void *Ptr) {
		this->Arena = Arena;
		this->Ptr = Ptr;
	}

	force_inline ~DeferredPop() {
		Pop(Arena, Ptr);
	}
};

// struct chained_arena

/* == Strings == */
typedef u8 char8;
struct string8 {
	char8 *Data;
	u32 Length;

	constexpr string8(char8 *Str) : Data(0), Length(0) {
		this->Data = (char8 *)Str;
		u32 Length = 0;
		while (*Str) {
			char8 C = *Str;

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
	constexpr string8(char8 *Str, u32 Length) : Data(0), Length(0) {
		this->Length = Length;
		this->Data = (char8 *)Str;
	}
};

constexpr u64 StringHash(const string8 &String);


/* == File / IO == */

/* == Threading == */
// thread_local storage
// work queue

/* == Assets == */

/* == Windowing / Input == */
void CreateWindow(memory_arena *Arena, const string8 &Title, u32 Width, u32 Height);
void ResizeWindow(u32 Width, u32 Height);
bool ShouldWindowClose();

/* == Ray tracing == */

/* == Rasterization == */

/* == Sound == */

struct SoundHandle {
	u32 H;
	force_inline explicit operator u32() const { return H; }
};

void InitSoundEngine();
SoundHandle PlaySound(u64 Hash);
void StopSound(SoundHandle Handle);
