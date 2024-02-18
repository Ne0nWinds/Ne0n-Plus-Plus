/* == u32x2 == */
MATHCALL u32x2 operator+(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_add_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator-(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_sub_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator*(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_mul_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator/(const u32x2 &a, const u32x2 &b) {
	u32x2 Result = 0;
	Result.x /= b.x;
	Result.y /= b.y;
	return Result;
}
MATHCALL u32x2 operator-(const u32x2 &a) {
	u32x2 Result;
	Result = ~a + 1;
	return (u32x2)Result;
}
MATHCALL u32x2 operator==(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_cmpeq_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator!=(const u32x2 &a, const u32x2 &b) {
	xmm Equal = _mm_cmpeq_epi32(xmm(a), xmm(b));
	u32x2 Result = (u32x2)Equal;
	Result = ~Result;
	return Result;
}
MATHCALL u32x2 operator>(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_cmpgt_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator<(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_cmplt_epi32(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator&(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_and_si128(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator|(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_or_si128(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator^(const u32x2 &a, const u32x2 &b) {
	xmm Result = _mm_xor_si128(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator~(const u32x2 &a) {
	xmm Throwaway = xmm((u32)0);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_ps(AllOnes, xmm(a));
	return (u32x2)Result;
}
MATHCALL u32x2 operator<<(const u32x2 &a, const u32 &b) {
	xmm Result = _mm_slli_epi32(xmm(a), b);
	return (u32x2)Result;
}
MATHCALL u32x2 operator>>(const u32x2 &a, const u32 &b) {
	xmm Result = _mm_srli_epi32(xmm(a), b);
	return (u32x2)Result;
}

/* == u32x3 ==*/
MATHCALL u32x3 operator+(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_add_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator-(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_sub_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator*(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_mul_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator/(const u32x3 &a, const u32x3 &b) {
	u32x3 Result = 0;
	Result.x /= b.x;
	Result.y /= b.y;
	Result.z /= b.z;
	return Result;
}
MATHCALL u32x3 operator-(const u32x3 &a) {
	u32x3 Result;
	Result = ~a + 1;
	return (u32x3)Result;
}
MATHCALL u32x3 operator==(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_cmpeq_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator!=(const u32x3 &a, const u32x3 &b) {
	xmm Equal = _mm_cmpeq_epi32(xmm(a), xmm(b));
	u32x3 Result = (u32x3)Equal;
	Result = ~Result;
	return Result;
}
MATHCALL u32x3 operator>(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_cmpgt_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator<(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_cmplt_epi32(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator&(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_and_si128(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator|(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_or_si128(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator^(const u32x3 &a, const u32x3 &b) {
	xmm Result = _mm_xor_si128(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator~(const u32x3 &a) {
	xmm Throwaway = xmm((u32)0);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_ps(AllOnes, xmm(a));
	return (u32x3)Result;
}
MATHCALL u32x3 operator<<(const u32x3 &a, const u32 &b) {
	xmm Result = _mm_slli_epi32(xmm(a), b);
	return (u32x3)Result;
}
MATHCALL u32x3 operator>>(const u32x3 &a, const u32 &b) {
	xmm Result = _mm_srli_epi32(xmm(a), b);
	return (u32x3)Result;
}

/* == u32x4 ==*/
MATHCALL u32x4 operator+(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_add_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator-(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_sub_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator*(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_mul_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator/(const u32x4 &a, const u32x4 &b) {
	u32x4 Result = 0;
	Result.x /= b.x;
	Result.y /= b.y;
	Result.z /= b.z;
	Result.w /= b.w;
	return Result;
}
MATHCALL u32x4 operator-(const u32x4 &a) {
	u32x4 Result;
	Result = ~a + 1;
	return (u32x4)Result;
}
MATHCALL u32x4 operator==(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_cmpeq_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator!=(const u32x4 &a, const u32x4 &b) {
	xmm Equal = _mm_cmpeq_epi32(xmm(a), xmm(b));
	u32x4 Result = (u32x4)Equal;
	Result = ~Result;
	return Result;
}
MATHCALL u32x4 operator>(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_cmpgt_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator<(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_cmplt_epi32(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator&(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_and_si128(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator|(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_or_si128(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator^(const u32x4 &a, const u32x4 &b) {
	xmm Result = _mm_xor_si128(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator~(const u32x4 &a) {
	xmm Throwaway = xmm((u32)0);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_si128(AllOnes, xmm(a));
	return (u32x4)Result;
}
MATHCALL u32x4 operator<<(const u32x4 &a, const u32 &b) {
	xmm Result = _mm_slli_epi32(xmm(a), b);
	return (u32x4)Result;
}
MATHCALL u32x4 operator>>(const u32x4 &a, const u32 &b) {
	xmm Result = _mm_srli_epi32(xmm(a), b);
	return (u32x4)Result;
}

/* == v2 == */
MATHCALL v2 operator+(const v2 &a, const v2 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator-(const v2 &a, const v2 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator*(const v2 &a, const v2 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator/(const v2 &a, const v2 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator-(const v2 &a) {
	u32x2 Sign = SignBit;
	xmm Result = _mm_xor_ps(xmm(a), xmm(Sign));
	return (v2)Result;
}
MATHCALL u32x2 operator==(const v2 &a, const v2 &b) {
	xmm Result = _mm_cmpeq_ps(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator!=(const v2 &a, const v2 &b) {
	xmm Result = _mm_cmpneq_ps(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator>(const v2 &a, const v2 &b) {
	xmm Result = _mm_cmpgt_ps(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL u32x2 operator<(const v2 &a, const v2 &b) {
	xmm Result = _mm_cmplt_ps(xmm(a), xmm(b));
	return (u32x2)Result;
}
MATHCALL v2 operator&(const v2 &a, const u32x2 &b) {
	xmm Result = _mm_and_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator|(const v2 &a, const u32x2 &b) {
	xmm Result = _mm_or_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator^(const v2 &a, const u32x2 &b) {
	xmm Result = _mm_xor_ps(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator~(const v2 &a) {
	xmm Throwaway = xmm(a);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_ps(AllOnes, xmm(a));
	return (v2)Result;
}
MATHCALL v2 operator<<(const v2 &a, const u32 &b) {
	xmm Result = _mm_sll_epi32(xmm(a), xmm(b));
	return (v2)Result;
}
MATHCALL v2 operator>>(const v2 &a, const u32 &b) {
	xmm Result = _mm_srl_epi32(xmm(a), xmm(b));
	return (v2)Result;
}

/* == v3 == */
MATHCALL v3 operator+(const v3 &a, const v3 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator-(const v3 &a, const v3 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator*(const v3 &a, const v3 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator/(const v3 &a, const v3 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator-(const v3 &a) {
	u32x3 Sign = SignBit;
	xmm Result = _mm_xor_ps(xmm(a), xmm(Sign));
	return (v3)Result;
}
MATHCALL u32x3 operator==(const v3 &a, const v3 &b) {
	xmm Result = _mm_cmpeq_ps(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator!=(const v3 &a, const v3 &b) {
	xmm Result = _mm_cmpneq_ps(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator>(const v3 &a, const v3 &b) {
	xmm Result = _mm_cmpgt_ps(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL u32x3 operator<(const v3 &a, const v3 &b) {
	xmm Result = _mm_cmplt_ps(xmm(a), xmm(b));
	return (u32x3)Result;
}
MATHCALL v3 operator&(const v3 &a, const u32x3 &b) {
	xmm Result = _mm_and_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator|(const v3 &a, const u32x3 &b) {
	xmm Result = _mm_or_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator^(const v3 &a, const u32x3 &b) {
	xmm Result = _mm_xor_ps(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator~(const v3 &a) {
	xmm Throwaway = xmm(a);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_ps(AllOnes, xmm(a));
	return (v3)Result;
}
MATHCALL v3 operator<<(const v3 &a, const u32 &b) {
	xmm Result = _mm_sll_epi32(xmm(a), xmm(b));
	return (v3)Result;
}
MATHCALL v3 operator>>(const v3 &a, const u32 &b) {
	xmm Result = _mm_srl_epi32(xmm(a), xmm(b));
	return (v3)Result;
}

/* == v4 == */
MATHCALL v4 operator+(const v4 &a, const v4 &b) {
	xmm Result = _mm_add_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator-(const v4 &a, const v4 &b) {
	xmm Result = _mm_sub_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator*(const v4 &a, const v4 &b) {
	xmm Result = _mm_mul_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator/(const v4 &a, const v4 &b) {
	xmm Result = _mm_div_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator-(const v4 &a) {
	u32x4 Sign = SignBit;
	xmm Result = _mm_xor_ps(xmm(a), xmm(Sign));
	return (v4)Result;
}
MATHCALL u32x4 operator==(const v4 &a, const v4 &b) {
	xmm Result = _mm_cmpeq_ps(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator!=(const v4 &a, const v4 &b) {
	xmm Result = _mm_cmpneq_ps(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator>(const v4 &a, const v4 &b) {
	xmm Result = _mm_cmpgt_ps(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL u32x4 operator<(const v4 &a, const v4 &b) {
	xmm Result = _mm_cmplt_ps(xmm(a), xmm(b));
	return (u32x4)Result;
}
MATHCALL v4 operator&(const v4 &a, const u32x4 &b) {
	xmm Result = _mm_and_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator|(const v4 &a, const u32x4 &b) {
	xmm Result = _mm_or_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator^(const v4 &a, const u32x4 &b) {
	xmm Result = _mm_xor_ps(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator~(const v4 &a) {
	xmm Throwaway = xmm(a);
	xmm AllOnes = _mm_cmpeq_epi32(Throwaway, Throwaway);
	xmm Result = _mm_xor_ps(AllOnes, xmm(a));
	return (v4)Result;
}
MATHCALL v4 operator<<(const v4 &a, const u32 &b) {
	xmm Result = _mm_sll_epi32(xmm(a), xmm(b));
	return (v4)Result;
}
MATHCALL v4 operator>>(const v4 &a, const u32 &b) {
	xmm Result = _mm_srl_epi32(xmm(a), xmm(b));
	return (v4)Result;
}

/* == v8 / u32x8 == */
#if SIMD_WIDTH == 4
MATHCALL v8 operator+(const v8 &a, const v8 &b) {
	v8 Result = v8(a.V4[0] + b.V4[0], a.V4[1] + b.V4[1]);
	return Result;
}
MATHCALL v8 operator-(const v8 &a, const v8 &b) {
	v8 Result = v8(a.V4[0] - b.V4[0], a.V4[1] - b.V4[1]);
	return Result;
}
MATHCALL v8 operator*(const v8 &a, const v8 &b) {
	v8 Result = v8(a.V4[0] * b.V4[0], a.V4[1] * b.V4[1]);
	return Result;
}
MATHCALL v8 operator/(const v8 &a, const v8 &b) {
	v8 Result = v8(a.V4[0] / b.V4[0], a.V4[1] / b.V4[1]);
	return Result;
}
MATHCALL v8 operator-(const v8 &a) {
	v8 Result = v8(-a.V4[0], -a.V4[1]);
	return Result;
}
MATHCALL u32x8 operator==(const v8 &a, const v8 &b) {
	u32x8 Result = u32x8(a.V4[0] == b.V4[0], a.V4[1] == b.V4[1]);
	return Result;
}
MATHCALL u32x8 operator!=(const v8 &a, const v8 &b) {
	u32x8 Result = u32x8(a.V4[0] != b.V4[0], a.V4[1] != b.V4[1]);
	return Result;
}
MATHCALL u32x8 operator>(const v8 &a, const v8 &b) {
	u32x8 Result = u32x8(a.V4[0] > b.V4[0], a.V4[1] > b.V4[1]);
	return Result;
}
MATHCALL u32x8 operator<(const v8 &a, const v8 &b) {
	u32x8 Result = u32x8(a.V4[0] < b.V4[0], a.V4[1] < b.V4[1]);
	return Result;
}
MATHCALL v8 operator&(const v8 &a, const u32x8 &b) {
	v8 Result = v8(a.V4[0] & b.U32x4[0], a.V4[1] & b.U32x4[1]);
	return Result;
}
MATHCALL v8 operator|(const v8 &a, const u32x8 &b) {
	v8 Result = v8(a.V4[0] | b.U32x4[0], a.V4[1] | b.U32x4[1]);
	return Result;
}
MATHCALL v8 operator^(const v8 &a, const u32x8 &b) {
	v8 Result = v8(a.V4[0] ^ b.U32x4[0], a.V4[1] ^ b.U32x4[1]);
	return Result;
}
MATHCALL v8 operator~(const v8 &a) {
	v8 Result = v8(~a.V4[0], ~a.V4[1]);
	return Result;
}
MATHCALL v8 operator<<(const v8 &a, const u32 &b) {
	v8 Result = v8(a.V4[0] << b, a.V4[1] << b);
	return Result;
}
MATHCALL v8 operator>>(const v8 &a, const u32 &b) {
	v8 Result = v8(a.V4[0] >> b, a.V4[1] >> b);
	return Result;
}
MATHCALL u32x8 operator+(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] + b.U32x4[0], a.U32x4[1] + b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator-(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] - b.U32x4[0], a.U32x4[1] - b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator*(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] * b.U32x4[0], a.U32x4[1] * b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator/(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] / b.U32x4[0], a.U32x4[1] / b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator-(const u32x8 &a) {
	u32x8 Result = u32x8(-a.U32x4[0], -a.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator==(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] == b.U32x4[0], a.U32x4[1] == b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator!=(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] != b.U32x4[0], a.U32x4[1] != b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator>(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] > b.U32x4[0], a.U32x4[1] > b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator<(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] < b.U32x4[0], a.U32x4[1] < b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator&(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] & b.U32x4[0], a.U32x4[1] & b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator|(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] | b.U32x4[0], a.U32x4[1] | b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator^(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] ^ b.U32x4[0], a.U32x4[1] ^ b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator~(const u32x8 &a) {
	u32x8 Result = u32x8(~a.U32x4[0], ~a.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator<<(const u32x8 &a, const u32 &b) {
	u32x8 Result = u32x8(a.U32x4[0] << b, a.U32x4[1] << b);
	return Result;
}
MATHCALL u32x8 operator>>(const u32x8 &a, const u32 &b) {
	u32x8 Result = u32x8(a.U32x4[0] >> b, a.U32x4[1] >> b);
	return Result;
}
#elif SIMD_WIDTH == 8
MATHCALL v8 operator+(const v8 &a, const v8 &b) {
	ymm Result = _mm256_add_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator-(const v8 &a, const v8 &b) {
	ymm Result = _mm256_sub_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator*(const v8 &a, const v8 &b) {
	ymm Result = _mm256_mul_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator/(const v8 &a, const v8 &b) {
	ymm Result = _mm256_div_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator-(const v8 &a) {
	u32x8 Sign = SignBit;
	ymm Result = _mm256_xor_ps(ymm(a), ymm(Sign));
	return (v8)Result;
}
MATHCALL u32x8 operator==(const v8 &a, const v8 &b) {
	ymm Result = _mm256_cmp_ps(ymm(a), ymm(b), _CMP_EQ_OQ);
	return (u32x8)Result;
}
MATHCALL u32x8 operator!=(const v8 &a, const v8 &b) {
	ymm Result = _mm256_cmp_ps(ymm(a), ymm(b), _CMP_NEQ_OQ);
	return (u32x8)Result;
}
MATHCALL u32x8 operator>(const v8 &a, const v8 &b) {
	ymm Result = _mm256_cmp_ps(ymm(a), ymm(b), _CMP_GT_OQ);
	return (u32x8)Result;
}
MATHCALL u32x8 operator<(const v8 &a, const v8 &b) {
	ymm Result = _mm256_cmp_ps(ymm(a), ymm(b), _CMP_LT_OQ);
	return (u32x8)Result;
}
MATHCALL v8 operator&(const v8 &a, const u32x8 &b) {
	ymm Result = _mm256_and_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator|(const v8 &a, const u32x8 &b) {
	ymm Result = _mm256_or_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator^(const v8 &a, const u32x8 &b) {
	ymm Result = _mm256_xor_ps(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator~(const v8 &a) {
	ymm AllOnes = a == a;
	ymm Result = _mm256_xor_ps(AllOnes, ymm(a));
	return (v8)Result;
}
MATHCALL v8 operator<<(const v8 &a, const u32 &b) {
	ymm Result = _mm256_sllv_epi32(ymm(a), ymm(b));
	return (v8)Result;
}
MATHCALL v8 operator>>(const v8 &a, const u32 &b) {
	ymm Result = _mm256_srlv_epi32(ymm(a), ymm(b));
	return (v8)Result;
}

MATHCALL u32x8 operator+(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_add_epi32(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator-(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_sub_epi32(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator*(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_mul_epi32(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator/(const u32x8 &a, const u32x8 &b) {
	u32x8 Result = u32x8(a.U32x4[0] / b.U32x4[0], a.U32x4[1] / b.U32x4[1]);
	return Result;
}
MATHCALL u32x8 operator-(const u32x8 &a) {
	u32x8 Result;
	Result = ~a + 1;
	return Result;
}
MATHCALL u32x8 operator==(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_cmpeq_epi32(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator!=(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_cmpeq_epi32(ymm(a), ymm(b));
	return ~(u32x8)Result;
}
MATHCALL u32x8 operator>(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_cmpgt_epi32(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator<(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_cmpgt_epi32(ymm(a), ymm(b));
	return ~(u32x8)Result;
}
MATHCALL u32x8 operator&(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_and_si256(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator|(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_or_si256(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator^(const u32x8 &a, const u32x8 &b) {
	ymm Result = _mm256_xor_si256(ymm(a), ymm(b));
	return (u32x8)Result;
}
MATHCALL u32x8 operator~(const u32x8 &a) {
	ymm Zero = ymm((u32)0);
	ymm AllOnes = _mm256_cmpeq_epi32(Zero, Zero);
	ymm Result = _mm256_xor_si256(AllOnes, ymm(a));
	return (u32x8)Result;
}
MATHCALL u32x8 operator<<(const u32x8 &a, const u32 &b) {
	ymm Result = _mm256_slli_epi32(ymm(a), b);
	return (u32x8)Result;
}
MATHCALL u32x8 operator>>(const u32x8 &a, const u32 &b) {
	ymm Result = _mm256_srli_epi32(ymm(a), b);
	return (u32x8)Result;
}
#endif
