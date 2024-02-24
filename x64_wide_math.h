
struct u128 {
	u32x4 Value;

	force_inline constexpr u128() : Value((u32)0) { }
	force_inline constexpr u128(u32 n) : Value((u32)0) { Value.x = n; }
	force_inline constexpr u128(u32x4 n) : Value(n) { }
	force_inline operator bool() const { 
		return !IsZeroed(Value);
	}
};

MATHCALL u128 operator&(const u128 &a, const u128 &b) {
	u128 Result = a.Value & b.Value;
	return Result;
}
MATHCALL u128 operator^(const u128 &a, const u128 &b) {
	u128 Result = a.Value ^ b.Value;
	return Result;
}
MATHCALL u128 operator|(const u128 &a, const u128 &b) {
	u128 Result = a.Value | b.Value;
	return Result;
}
MATHCALL u128 operator~(u128 a) {
	u128 Result = ~a.Value;
	return Result;
}
