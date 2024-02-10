union xmm {
	v4 V4;
	__m128 m128;
	__m128i m128i;

	force_inline constexpr xmm(v2 a) : V4(a) { } // MOVSD
	force_inline constexpr xmm(v3 a) : V4(a) { }
	force_inline constexpr xmm(v4 a) : V4(a) { }
	force_inline constexpr xmm(__m128 a) : m128(a) { }
	force_inline constexpr xmm(__m128i a) : m128i(a) { }

	explicit operator v2() const { return { V4.x, V4.y }; }
	explicit operator v3() const { return { V4.x, V4.y, V4.z }; }
	explicit operator v4() const { return V4; }
	operator __m128() const { return m128; }
	operator __m128i() const { return m128i; }
};

#if SIMD_WIDTH == 8

union ymm {
	v8 V8;
	__m256 m256;
	__m256i m256i;

	force_inline constexpr ymm(v8 a) : V8(a) { }
	force_inline constexpr ymm(__m256 a) : m256(a) { }
	force_inline constexpr ymm(__m256i a) : m256i(a) { }
	explicit operator v8() const { return V8; }
};

#endif

MATHCALL v2 operator+(const v2 &a, const v2 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL void operator+=(v2 &a, const v2 &b) {
	a = a + b;
}
MATHCALL v2 operator-(const v2 &a, const v2 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL void operator-=(v2 &a, const v2 &b) {
	a = a - b;
}
MATHCALL v2 operator*(const v2 &a, const v2 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL void operator*=(v2 &a, const v2 &b) {
	a = a * b;
}
MATHCALL v2 operator/(const v2 &a, const v2 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL void operator/=(v2 &a, const v2 &b) {
	a = a / b;
}

MATHCALL v3 operator+(const v3 &a, const v3 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL void operator+=(v3 &a, const v3 &b) {
	a = a + b;
}
MATHCALL v3 operator-(const v3 &a, const v3 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL void operator-=(v3 &a, const v3 &b) {
	a = a - b;
}
MATHCALL v3 operator*(const v3 &a, const v3 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL void operator*=(v3 &a, const v3 &b) {
	a = a * b;
}
MATHCALL v3 operator/(const v3 &a, const v3 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL void operator/=(v3 &a, const v3 &b) {
	a = a / b;
}

MATHCALL v4 operator+(const v4 &a, const v4 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL void operator+=(v4 &a, const v4 &b) {
	a = a + b;
}
MATHCALL v4 operator-(const v4 &a, const v4 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL void operator-=(v4 &a, const v4 &b) {
	a = a - b;
}
MATHCALL v4 operator*(const v4 &a, const v4 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL void operator*=(v4 &a, const v4 &b) {
	a = a * b;
}
MATHCALL v4 operator/(const v4 &a, const v4 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL void operator/=(v4 &a, const v4 &b) {
	a = a / b;
}

#if SIMD_WIDTH == 4
MATHCALL v8 operator+(const v8 &a, const v8 &b) {
	xmm xmm0 = _mm_add_ps(xmm(a.V4[0]), xmm(b.V4[0]));
	xmm xmm1 = _mm_add_ps(xmm(a.V4[1]), xmm(b.V4[1]));
	return { (v4)xmm0, (v4)xmm1 };
}
MATHCALL void operator+=(v8 &a, const v8 &b) {
	a = a + b;
}
MATHCALL v8 operator-(const v8 &a, const v8 &b) {
	xmm xmm0 = _mm_sub_ps(xmm(a.V4[0]), xmm(b.V4[0]));
	xmm xmm1 = _mm_sub_ps(xmm(a.V4[1]), xmm(b.V4[1]));
	return { (v4)xmm0, (v4)xmm1 };
}
MATHCALL void operator-=(v8 &a, const v8 &b) {
	a = a - b;
}
MATHCALL v8 operator*(const v8 &a, const v8 &b) {
	xmm xmm0 = _mm_mul_ps(xmm(a.V4[0]), xmm(b.V4[0]));
	xmm xmm1 = _mm_mul_ps(xmm(a.V4[1]), xmm(b.V4[1]));
	return { (v4)xmm0, (v4)xmm1 };
}
MATHCALL void operator*=(v8 &a, const v8 &b) {
	a = a * b;
}
MATHCALL v8 operator/(const v8 &a, const v8 &b) {
	xmm xmm0 = _mm_div_ps(xmm(a.V4[0]), xmm(b.V4[0]));
	xmm xmm1 = _mm_div_ps(xmm(a.V4[1]), xmm(b.V4[1]));
	return { (v4)xmm0, (v4)xmm1 };
}
MATHCALL void operator/=(v8 &a, const v8 &b) {
	a = a / b;
}
#elif SIMD_WIDTH == 8
MATHCALL v8 operator+(const v8 &a, const v8 &b) {
	ymm ymm0 = _mm256_add_ps(ymm(a), ymm(b));
	return (v8)ymm0;
}
MATHCALL void operator+=(v8 &a, const v8 &b) {
	a = a + b;
}
MATHCALL v8 operator-(const v8 &a, const v8 &b) {
	ymm ymm0 = _mm256_sub_ps(ymm(a), ymm(b));
	return (v8)ymm0;
}
MATHCALL void operator-=(v8 &a, const v8 &b) {
	a = a - b;
}
MATHCALL v8 operator*(const v8 &a, const v8 &b) {
	ymm ymm0 = _mm256_mul_ps(ymm(a), ymm(b));
	return (v8)ymm0;
}
MATHCALL void operator*=(v8 &a, const v8 &b) {
	a = a * b;
}
MATHCALL v8 operator/(const v8 &a, const v8 &b) {
	ymm ymm0 = _mm256_div_ps(ymm(a), ymm(b));
	return (v8)ymm0;
}
MATHCALL void operator/=(v8 &a, const v8 &b) {
	a = a / b;
}
#endif
