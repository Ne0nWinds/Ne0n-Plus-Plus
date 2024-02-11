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

#define SIMD_WIDTH 4 // Most modern CPUs have at least a width of 4
#ifndef SIMD_WIDTH
	#ifdef PLATFORM_x64
		#if defined(__AVX2__)
			#define SIMD_WIDTH 8
		#endif
	#endif
#endif

/* == Math == */
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

struct alignas(8) v2 {
	f32 x, y;

	force_inline constexpr v2() : x(0.0f), y(0.0f) { }
	force_inline constexpr v2(f32 n) : x(n), y(n) { }
	force_inline constexpr v2(f32 _x, f32 _y) : x(_x), y(_y) { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 2);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

MATHCALL v2 operator+(const v2 &a, const v2 &b);
MATHCALL void operator+=(v2 &a, const v2 &b);
MATHCALL v2 operator-(const v2 &a, const v2 &b);
MATHCALL void operator-=(v2 &a, const v2 &b);
MATHCALL v2 operator*(const v2 &a, const v2 &b);
MATHCALL void operator*=(v2 &a, const v2 &b);
MATHCALL v2 operator/(const v2 &a, const v2 &b);
MATHCALL void operator/=(v2 &a, const v2 &b);

MATHCALL v2 operator&(const v2 &a, const u32x2 &b);
MATHCALL void operator&=(v2 &a, const u32x2 &b);

struct alignas(16) v3 {
	f32 x, y, z;

	force_inline constexpr v3() : x(0.0f), y(0.0f), z(0.0f) { }
	force_inline constexpr v3(f32 n) : x(n), y(n), z(n) { }
	force_inline constexpr v3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) { }
	explicit force_inline constexpr v3(const v2& a) : x(a.x), y(a.y), z(0.0f) { }
	force_inline constexpr v3(const v2& a, f32 b) : x(a.x), y(a.y), z(b) { }
	force_inline constexpr v3(f32 a, const v2& b) : x(a), y(b.x), z(b.y) { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 3);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

MATHCALL v3 operator+(const v3 &a, const v3 &b);
MATHCALL void operator+=(v3 &a, const v3 &b);
MATHCALL v3 operator-(const v3 &a, const v3 &b);
MATHCALL void operator-=(v3 &a, const v3 &b);
MATHCALL v3 operator*(const v3 &a, const v3 &b);
MATHCALL void operator*=(v3 &a, const v3 &b);
MATHCALL v3 operator/(const v3 &a, const v3 &b);
MATHCALL void operator/=(v3 &a, const v3 &b);

MATHCALL v3 operator&(const v3 &a, const u32x3 &b);
MATHCALL void operator&=(v3 &a, const u32x3 &b);

struct alignas(16) v4 {
	f32 x, y, z, w;

	force_inline constexpr v4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
	force_inline constexpr v4(f32 n) : x(n), y(n), z(n), w(n) { }
	force_inline constexpr v4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) { }
	explicit force_inline constexpr v4(const v2& a) : x(a.x), y(a.y), z(0.0f), w(0.0f) { }
	explicit force_inline constexpr v4(const v3& a) : x(a.x), y(a.y), z(a.z), w(0.0f) { }
	force_inline constexpr v4(const v2& a, f32 b, f32 c) : x(a.x), y(a.y), z(b), w(c) { }
	force_inline constexpr v4(const v2& a, const v2& b) : x(a.x), y(a.y), z(b.x), w(b.y) { }
	force_inline constexpr v4(const v3& a, f32 b) : x(a.x), y(a.y), z(a.z), w(b) { }
	force_inline constexpr v4(f32 a, const v3& b) : x(a), y(b.x), z(b.y), w(b.z) { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 3);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

MATHCALL v4 operator+(const v4 &a, const v4 &b);
MATHCALL void operator+=(v4 &a, const v4 &b);
MATHCALL v4 operator-(const v4 &a, const v4 &b);
MATHCALL void operator-=(v4 &a, const v4 &b);
MATHCALL v4 operator*(const v4 &a, const v4 &b);
MATHCALL void operator*=(v4 &a, const v4 &b);
MATHCALL v4 operator/(const v4 &a, const v4 &b);
MATHCALL void operator/=(v4 &a, const v4 &b);

MATHCALL v4 operator&(const v4 &a, const u32x4 &b);
MATHCALL void operator&=(v4 &a, const u32x4 &b);

struct alignas(16) v8 {
	union {
		struct { f32 x, y, z, w; };
		f32 Data[8];
		v4 V4[2];
	};

	force_inline v8() : Data {0.0f} { }
	force_inline v8(f32 n) : Data {n,n,n,n,n,n,n,n} { }
	force_inline v8(v4 a, v4 b) : V4 { a, b } { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

MATHCALL v8 operator+(const v8 &a, const v8 &b);
MATHCALL void operator+=(v8 &a, const v8 &b);
MATHCALL v8 operator-(const v8 &a, const v8 &b);
MATHCALL void operator-=(v8 &a, const v8 &b);
MATHCALL v8 operator*(const v8 &a, const v8 &b);
MATHCALL void operator*=(v8 &a, const v8 &b);
MATHCALL v8 operator/(const v8 &a, const v8 &b);
MATHCALL void operator/=(v8 &a, const v8 &b);

struct alignas(8) u32x2 {
	union {
		struct { u32 x, y; };
		u32 Data[2];
		u64 _u64;
	};
	force_inline constexpr u32x2() : x(0), y(0) { }
	explicit force_inline constexpr u32x2(u32 n) : x(n), y(n) { }
	explicit force_inline constexpr u32x2(bool n) : _u64(~(u64)n + 1) { }
	force_inline constexpr u32x2(u32 _x, u32 _y) : x(_x), y(_y) { }
};

struct alignas(16) u32x3 {
	union {
		struct { u32 x, y, z; };
		u32 Data[4];
		u64 _u64[2];
	};
	force_inline constexpr u32x3() : _u64 { 0 } { }
	explicit force_inline constexpr u32x3(u32 n) : Data { n, n, n, n } { }
	explicit force_inline constexpr u32x3(u32x2 a) : x(a.x), y(a.y), z(0) { }
	force_inline constexpr u32x3(u32x2 a, u32 b) : x(a.x), y(a.y), z(b) { }
	explicit force_inline constexpr u32x3(bool n) : _u64 { ~(u64)n + 1, ~(u64)n + 1 } { }
	force_inline constexpr u32x3(u32 _x, u32 _y, u32 _z) : x(_x), y(_y), z(_z) { }
};

struct alignas(16) u32x4 {
	union {
		struct { u32 x, y, z, w; };
		u32 Data[4];
		u64 _u64[2];
	};
	force_inline constexpr u32x4() : _u64 { 0 } { }
	explicit force_inline constexpr u32x4(u32 n) : Data { n, n, n, n } { }
	explicit force_inline constexpr u32x4(u32x2 n) : x(n.x), y(n.y), z(0), w(0) { }
	explicit force_inline constexpr u32x4(u32x3 n) : x(n.x), y(n.y), z(n.z), w(0) { }
	explicit force_inline constexpr u32x4(bool n) : _u64 { ~(u64)n + 1, ~(u64)n + 1 } { }
	force_inline constexpr u32x4(u32 _x, u32 _y, u32 _z, u32 _w) : x(_x), y(_y), z(_z), w(_z) { }
};

#if defined(PLATFORM_X64)
	union xmm {
		v4 V4;
		u32x4 U32x4;
		__m128 m128;
		__m128i m128i;

		force_inline constexpr xmm(f32 a) : V4(0.0f) { V4.x = a; } // movss
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
		force_inline operator __m128() const { return m128; }
		force_inline operator __m128i() const { return m128i; }
	};

	#if SIMD_WIDTH == 8
		union ymm {
			v8 V8;
			__m256 m256;
			__m256i m256i;

			force_inline constexpr ymm(v8 a) : V8(a) { }
			force_inline constexpr ymm(__m256 a) : m256(a) { }
			force_inline constexpr ymm(__m256i a) : m256i(a) { }
			force_inline explicit operator v8() const { return V8; }
		};
	#endif

	#include "x64_operators.h"
#else
	#include "operators.h"
#endif

#define abs(a) ((a < 0) ? a * -1 : a)
#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)
static constexpr f32 F32Epsilon = 1e-5f;
static constexpr f32 F32Min = 1e-30f;
static constexpr f32 F32Max = 1e30f;
static constexpr f32 PI32 = 3.14159265358979323846f;
static constexpr u32 SignBit = 0x8000'0000;

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
MATHCALL f32 f32_atan2(f32 y, f32 x);

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

/* == Psuedo Randomnes == */
struct random_state64 {
	u64 Seed;
};
struct random_state128 {
	u64 Seed1, Seed2;
};

MATHCALL u32 u32_random(random_state64 *random_state);
MATHCALL u32 u32_random(random_state128 *random_state);
MATHCALL f32 f32_random(random_state64 *random_state);
MATHCALL f32 f32_random(random_state128 *random_state);

#define RANDOM_ALGORITHM_PCG 1
#define RANDOM_ALGORITHM_LCG 2
#define RANDOM_ALGORITHM_XORSHIFT 3

#ifndef RANDOM_ALGORITHM
	#define RANDOM_ALGORITHM RANDOM_ALGORITHM_PCG
#endif

/* == SIMD Helpers == */

// TODO: u8x / Text Parsing
struct u32x;
struct f32x;
struct v2x;
struct v3x;
struct v4x;
struct u128;
struct u256;

#if SIMD_WIDTH == 4
	#include "simd_helpers_4x.h"
#elif SIMD_WIDTH == 8
	#include "simd_helpers_8x.h"
#else
	#error "SIMD Width Not Supported"
#endif

/* == Memory == */

#define KB(b) (b * 1024)
#define MB(b) (KB(b) * 1024)
#define GB(b) (MB(b) * 1024LLU)
#define TB(b) (GB(b) * 1024LLU)
