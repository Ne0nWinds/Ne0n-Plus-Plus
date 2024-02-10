// Slow but portable math functions

#undef abs
#undef min
#undef max
#include <math.h>
#define abs(a) ((a < 0) ? a * -1 : a)
#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

MATHCALL s32 s32_abs(s32 a) {
	return abs(a);
}
MATHCALL s64 s64_abs(s64 a) {
	return abs(a);
}
MATHCALL u32 u32_min(u32 a, u32 b) {
	return min(a, b);
}
MATHCALL u64 u64_min(u64 a, u64 b) {
	return min(a, b);
}
MATHCALL s32 s32_min(s32 a, s32 b) {
	return min(a, b);
}
MATHCALL s64 s64_min(s64 a, s64 b) {
	return min(a, b);
}
MATHCALL u32 u32_max(u32 a, u32 b) {
	return max(a, b);
}
MATHCALL u64 u64_max(u64 a, u64 b) {
	return max(a, b);
}
MATHCALL s32 s32_max(s32 a, s32 b) {
	return max(a, b);
}
MATHCALL s64 s64_max(s64 a, s64 b) {
	return max(a, b);
}

MATHCALL u32 u32_popcnt(u32 a) {
	u32 Result = 0;
	for (u32 i = 0; i < 32; ++i) {
		if (a & (i << 1)) {
			Result += 1;
		}
	}
	return Result;
}
MATHCALL u64 u64_popcnt(u32 a) {
	u32 Result = 0;
	for (u32 i = 0; i < 64; ++i) {
		if (a & (i << 1)) {
			Result += 1;
		}
	}
	return Result;
}

MATHCALL f32 f32_round(f32 a) {
	u32 AsInt = a + 0.5f;
	return (f32)AsInt;
}
MATHCALL f32 f32_ceil(f32 a) {
	u32 SmallestF32UnderOne = 0x3f7ffffe;
	u32 AsInt = a + *(f32 *)&SmallestF32UnderOne;
	return (f32)AsInt;
}
MATHCALL f32 f32_floor(f32 a) {
	return (u32)a;
}
MATHCALL f32 f32_sqrt(f32 a) {
	return sqrtf(a);
}
MATHCALL f32 f32_inv_sqrt(f32 a) {
	return 1.0f / sqrtf(a);
}
MATHCALL f32 f32_max(f32 a, f32 b) {
	return max(a, b);
}
MATHCALL f32 f32_min(f32 a, f32 b) {
	return min(a, b);
}
MATHCALL f32 f32_lerp(f32 a, f32 b, f32 t) {
	return (1 - t) * a + t * b;
}
MATHCALL f32 f32_square(f32 a) {
	return a * a;
}
MATHCALL f32 f32_negate(f32 a) {
	u32 SignBit = 0x80000000;
	*(u32 *)&a ^= SignBit;
	return a;
}
MATHCALL f32 f32_sign(f32 a) {
	u32 SignBit = 0x80000000;
	f32 Result = 1.0f;
	*(u32 *)&Result |= *(u32 *)&a & SignBit;
	return Result;
}
MATHCALL f32 f32_abs(f32 a) {
	return abs(a);
}
MATHCALL f32 f32_mod(f32 a, f32 b) {
	return fmodf(a, b);
}
MATHCALL f32 f32_clamp(f32 a, f32 min, f32 max) {
	if (a < min) return min;
	if (a > max) return max;
	return a;
}

MATHCALL f32 f32_radians(f32 degrees) {
	return degrees * (PI32 / 180.0f);
}
MATHCALL f32 f32_sin(f32 radians) {
	return sinf(radians);
}
MATHCALL f32 f32_cos(f32 radians) {
	return cosf(radians);
}
MATHCALL f32 f32_tan(f32 radians) {
	return tanf(radians);
}
MATHCALL f32 f32_atan2(f32 y, f32 x) {
	return atan2f(y, x);
}

MATHCALL f32 v2_dot(const v2 &a, const v2 &b) {
	return a.x * b.x + a.y * b.y;
}
MATHCALL f32 v3_dot(const v3 &a, const v3 &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
MATHCALL f32 v4_dot(const v4 &a, const v4 &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
MATHCALL f32 v2_length_sq(const v2 &a) {
	return v2_dot(a, a);
}
MATHCALL f32 v3_length_sq(const v3 &a) {
	return v3_dot(a, a);
}
MATHCALL f32 v4_length_sq(const v4 &a) {
	return v4_dot(a, a);
}
MATHCALL f32 v2_length(const v2 &a) {
	return f32_sqrt(v2_length_sq(a));
}
MATHCALL f32 v3_length(const v3 &a) {
	return f32_sqrt(v3_length_sq(a));
}
MATHCALL f32 v4_length(const v4 &a) {
	return f32_sqrt(v4_length_sq(a));
}
MATHCALL v2 v2_normalize(const v2 &a) {
	f32 LengthSquared = v2_length_sq(a);
	if (LengthSquared < F32Epsilon) {
		f32 Length = f32_sqrt(LengthSquared);
		return a / Length;
	}
	return 0.0f;
}
MATHCALL v3 v3_normalize(const v3 &a) {
	f32 LengthSquared = v3_length_sq(a);
	if (LengthSquared < F32Epsilon) {
		f32 Length = f32_sqrt(LengthSquared);
		return a / Length;
	}
	return 0.0f;
}
MATHCALL v4 v4_normalize(const v4 &a) {
	f32 LengthSquared = v4_length_sq(a);
	if (LengthSquared < F32Epsilon) {
		f32 Length = f32_sqrt(LengthSquared);
		return a / Length;
	}
	return 0.0f;
}
MATHCALL v3 v3_cross(const v3 &a, const v3 &b) {
	v3 Result;
	Result.x = a.y * b.z - a.z * b.y;
	Result.y = a.z * b.x - a.x * b.z;
	Result.z = a.x * b.y - a.y * b.x;
	return Result;
}

MATHCALL v2 v2_lerp(const v2 &a, const v2 &b, f32 t) {
	return (1.0f - t) * a + t * b;
}
MATHCALL v3 v3_lerp(const v3 &a, const v3 &b, f32 t) {
	return (1.0f - t) * a + t * b;
}
MATHCALL v4 v4_lerp(const v4 &a, const v4 &b, f32 t) {
	return (1.0f - t) * a + t * b;
}
