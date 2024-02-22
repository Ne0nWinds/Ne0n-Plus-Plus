s32 s32_abs(s32 a) {
	u32 SignExtend = a >> 31;
	u32 XorResult = SignExtend ^ a;
	u32 Result = XorResult - SignExtend;
	return Result;
}
MATHCALL s64 s64_abs(s64 a) {
	u32 SignExtend = a >> 63;
	u32 XorResult = SignExtend ^ a;
	u32 Result = XorResult - SignExtend;
	return Result;
}
MATHCALL u32 u32_min(u32 a, u32 b) {
	u32 DOZ = (a - b) & -(a >= b);
	u32 Result = a - DOZ;
	return Result;
}
MATHCALL u64 u64_min(u64 a, u64 b) {
	u64 DOZ = (a - b) & -(a >= b);
	u64 Result = a - DOZ;
	return Result;
}
MATHCALL s32 s32_min(s32 a, s32 b) {
	s32 DOZ = (a - b) & -(a >= b);
	s32 Result = a - DOZ;
	return Result;
}
MATHCALL s64 s64_min(s64 a, s64 b) {
	s64 DOZ = (a - b) & -(a >= b);
	s64 Result = a - DOZ;
	return Result;
}
MATHCALL u32 u32_max(u32 a, u32 b) {
	u32 DOZ = (a - b) & -(a >= b);
	u32 Result = b + DOZ;
	return Result;
}
MATHCALL u64 u64_max(u64 a, u64 b) {
	u64 DOZ = (a - b) & -(a >= b);
	u64 Result = b + DOZ;
	return Result;
}
MATHCALL s32 s32_max(s32 a, s32 b) {
	s32 DOZ = (a - b) & -(a >= b);
	s32 Result = b + DOZ;
	return Result;
}
MATHCALL s64 s64_max(s64 a, s64 b) {
	s64 DOZ = (a - b) & -(a >= b);
	s64 Result = b + DOZ;
	return Result;
}

MATHCALL u32 u32_popcnt(u32 a) {
	u32 Result = _mm_popcnt_u32(a);
	return Result;
}
MATHCALL u64 u64_popcnt(u32 a) {
	u64 Result = _mm_popcnt_u64(a);
	return Result;
}
MATHCALL u32 u32_roundup_pw2(u32 a, u32 pw2) {
	Assert(u32_popcnt(pw2) == 1);
	u32 n = pw2 - 1;
	a += n;
	a &= ~n;
	return a;
}
MATHCALL u64 u64_roundup_pw2(u64 a, u64 pw2) {
	Assert(u64_popcnt(pw2) == 1);
	u64 n = pw2 - 1;
	a += n;
	a &= ~n;
	return a;
}

MATHCALL f32 f32_round(f32 a) {
	xmm xmm0 = a;
	xmm0 = _mm_round_ss(xmm0, xmm0, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	return (f32)xmm0;
}
MATHCALL f32 f32_ceil(f32 a) {
	xmm xmm0 = a;
	xmm0 = _mm_round_ss(xmm0, xmm0, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
	return (f32)xmm0;
}
MATHCALL f32 f32_floor(f32 a) {
	xmm xmm0 = a;
	xmm0 = _mm_round_ss(xmm0, xmm0, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
	return (f32)xmm0;
}
MATHCALL f32 f32_sqrt(f32 a) {
	xmm xmm0 = _mm_sqrt_ss(xmm(a));
	return (f32)xmm0;
}
MATHCALL f32 f32_inv_sqrt(f32 a) {
	xmm xmm0 = _mm_rsqrt_ss(xmm(a));
	return (f32)xmm0;
}
MATHCALL f32 f32_max(f32 a, f32 b) {
	xmm xmm0 = _mm_max_ss(xmm(a), xmm(b));
	return (f32)xmm0;
}
MATHCALL f32 f32_min(f32 a, f32 b) {
	xmm xmm0 = _mm_min_ss(xmm(a), xmm(b));
	return (f32)xmm0;
}
MATHCALL f32 f32_lerp(f32 a, f32 b, f32 t) {
	return (1.0f - t) * a + t * b;
}
MATHCALL f32 f32_square(f32 a) {
	return a * a;
}
MATHCALL f32 f32_negate(f32 a) {
	*(u32 *)&a ^= SignBit;
	return a;
}
MATHCALL f32 f32_sign(f32 a) {
	f32 Result = 1.0f;
	*(u32 *)&Result |= (SignBit & *(u32 *)&a);
	return Result;
}
MATHCALL f32 f32_abs(f32 a) {
	u32 NotSign = ~SignBit;
	*(u32 *)&a &= NotSign;
	return a;
}
MATHCALL f32 f32_mod(f32 a, f32 b) {
	Assert(b > F32Epsilon);
	f32 DivisionResult = a / b;
	f32 NearestInt = f32_round(DivisionResult);
	f32 Result = a - (NearestInt * b);
	return Result;
}
MATHCALL f32 f32_clamp(f32 a, f32 Min, f32 Max) {
	Assert(Min < Max);
	a = f32_min(a, Max);
	a = f32_max(a, Min);
	return a;
}

MATHCALL f32 f32_madd(f32 a, f32 b, f32 c) {
#if defined(__AVX2__) | defined(__FMA__)
	xmm Result = _mm_fmadd_ss(xmm(a), xmm(b), xmm(c));
	return (f32)Result;
#else
	return a * b + c;
#endif
}

MATHCALL f32 f32_radians(f32 Degrees) {
	return Degrees * (PI32 / 180.0f);
}

// TODO: These trig functions can be much faster and more accurate
MATHCALL f32 f32_sin(f32 Radians) {
	Assert(f32_abs(Radians) < PI32 * 2.0f);

	constexpr f32 HalfPI32 = PI32 / 2.0;

	{
		f32 DivisionResult = Radians * (1.0f / PI32);
		f32 NearestInt = f32_round(DivisionResult);
		Radians = Radians - (NearestInt * PI32);
	}
	if (Radians > HalfPI32) {
		Radians = HalfPI32 - (Radians - HalfPI32);
	}
	if (Radians < -HalfPI32) {
		Radians = -HalfPI32 - (Radians + HalfPI32);
	}

	constexpr f32 b = 1.0 / 6.0;
	constexpr f32 c = 1.0 / 120.0;
	f32 RadiansSquared = Radians * Radians;
	f32 RadiansCubed = RadiansSquared * Radians;
	f32 RadiansQuintic = RadiansSquared * RadiansSquared * Radians;
	f32 Result = Radians - b * RadiansCubed + c * RadiansQuintic;
	return f32_clamp(Result, 0.0f, 1.0f);
}
MATHCALL f32 f32_cos(f32 Radians) {
	return f32_sin(Radians + PI32 / 2.0f);
}
MATHCALL f32 f32_tan(f32 Radians) {
	return f32_sin(Radians) / f32_cos(Radians);
}
MATHCALL f32 f32_atan2(f32 y, f32 x) {
	// TODO: implementation
	return 0;
}

MATHCALL f32 v2_dot(const v2 &a, const v2 &b) {
	v2 MulResult = a * b;
	return MulResult.x + MulResult.y;
}
MATHCALL f32 v3_dot(const v3 &a, const v3 &b) {
	v3 MulResult = a * b;
	return MulResult.x + MulResult.y + MulResult.z;
}
MATHCALL f32 v4_dot(const v4 &a, const v4 &b) {
#if defined(__AVX__) | defined(__SSSE4_1__)
	// NOTE: this instruction offers no performance benefit, only in code size
	xmm Result = _mm_dp_ps(xmm(a), xmm(b), 0xF1);
	return (f32)Result;
#else
	v4 MulResult = a * b;
	return MulResult.x + MulResult.y + MulResult.z + MulResult.w;
#endif
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
	f32 LengthSquared = v2_dot(a, a);
	f32 Length = f32_sqrt(LengthSquared);
	return Length;
}
MATHCALL f32 v3_length(const v3 &a) {
	f32 LengthSquared = v3_dot(a, a);
	f32 Length = f32_sqrt(LengthSquared);
	return Length;
}
MATHCALL f32 v4_length(const v4 &a) {
	f32 LengthSquared = v4_dot(a, a);
	f32 Length = f32_sqrt(LengthSquared);
	return Length;
}
MATHCALL v2 v2_normalize(const v2 &a) {
	f32 LengthSquared = v2_length_sq(a);

	bool LengthGreaterThanZero = LengthSquared > F32Epsilon;
	u32x2 MoveMask = u32x2(LengthGreaterThanZero);

	f32 Length = f32_sqrt(LengthSquared);
	v2 Result = a / Length;
	Result &= MoveMask;

	return Result;
}
MATHCALL v3 v3_normalize(const v3 &a) {
	f32 LengthSquared = v3_length_sq(a);

	bool LengthGreaterThanZero = LengthSquared > F32Epsilon;
	u32x3 MoveMask = u32x3(LengthGreaterThanZero);

	f32 Length = f32_sqrt(LengthSquared);
	v3 Result = a / Length;
	Result &= MoveMask;

	return Result;
}
MATHCALL v4 v4_normalize(const v4 &a) {
	f32 LengthSquared = v4_length_sq(a);

	bool LengthGreaterThanZero = LengthSquared > F32Epsilon;
	u32x4 MoveMask = u32x4(LengthGreaterThanZero);

	f32 Length = f32_sqrt(LengthSquared);
	v4 Result = a / Length;
	Result &= MoveMask;

	return Result;
}
MATHCALL v3 v3_cross(v3 a, v3 b) {
	v3 Result;
	Result.x = a.y * b.z - a.z * b.y;
	Result.y = a.z * b.x - a.x * b.z;
	Result.z = a.x * b.y - a.y * b.x;
	return Result;
}

MATHCALL v2 v2_lerp(const v2 &a, const v2 &b, f32 t) {
	v2 Result = (1.0f - t) * a + t * b;
	return Result;
}
MATHCALL v3 v3_lerp(const v3 &a, const v3 &b, f32 t) {
	v3 Result = (1.0f - t) * a + t * b;
	return Result;
}
MATHCALL v4 v4_lerp(const v4 &a, const v4 &b, f32 t) {
	v4 Result = (1.0f - t) * a + t * b;
	return Result;
}

MATHCALL bool IsZeroed(const u32x2 &a) {
	const xmm xmm0 = xmm(a);
	s32 Result = _mm_testz_si128(xmm0, xmm0);
	return Result != 0;
}
MATHCALL bool IsZeroed(const u32x3 &a) {
	const xmm xmm0 = xmm(a);
	s32 Result = _mm_testz_si128(xmm0, xmm0);
	return Result != 0;
}
MATHCALL bool IsZeroed(const u32x4 &a) {
	const xmm xmm0 = xmm(a);
	s32 Result = _mm_testz_si128(xmm0, xmm0);
	return Result != 0;
}
#if SIMD_WIDTH == 4
MATHCALL bool IsZeroed(const u32x8 &a) {
	const xmm xmm0 = xmm(a.U32x4[0]);
	const xmm xmm1 = xmm(a.U32x4[1]);
	bool Result1 = _mm_testz_si128(xmm0, xmm0) != 0;
	bool Result2 = _mm_testz_si128(xmm1, xmm1) != 0;
	return Result1 & Result2;
}
#elif SIMD_WIDTH == 8
MATHCALL bool IsZeroed(const u32x8 &a) {
	const ymm ymm0 = ymm(a);
	s32 Result = _mm256_testz_si256(ymm0, ymm0);
	return Result != 0;
}
#endif
