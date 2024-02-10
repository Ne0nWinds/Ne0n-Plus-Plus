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
