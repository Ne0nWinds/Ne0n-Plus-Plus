
struct u128 {
	u32x4 Value;

	force_inline constexpr u128() : Value((u32)0) { }
	force_inline constexpr u128(u32 n) : Value(n) { }
	force_inline constexpr u128(u32x4 n) : Value(n) { }
	force_inline operator bool() const { 
		return !IsZeroed(Value);
	}
};

struct u256 {
	u32x8 Value;

	force_inline constexpr u256() : Value((u32)0) { }
	force_inline constexpr u256(u32 n) : Value(n) { }
	force_inline constexpr u256(u32x8 n) : Value(n) { }

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
MATHCALL u128 operator<<(const u128 &a, const u32 b) {
	u128 Result = a.Value << b;
	return Result;
}
MATHCALL u128 operator>>(const u128 &a, const u32 b) {
	u128 Result = a.Value >> b;
	return Result;
}

MATHCALL u256 operator&(const u256 &a, const u256 &b) {
	u256 Result = a.Value & b.Value;
	return Result;
}
MATHCALL u256 operator^(const u256 &a, const u256 &b) {
	u256 Result = a.Value ^ b.Value;
	return Result;
}
MATHCALL u256 operator|(const u256 &a, const u256 &b) {
	u256 Result = a.Value | b.Value;
	return Result;
}
MATHCALL u256 operator~(u256 a) {
	u256 Result = ~a.Value;
	return Result;
}
MATHCALL u256 operator<<(const u256 &a, const u32 b) {
	u256 Result = a.Value << b;
	return Result;
}
MATHCALL u256 operator>>(const u256 &a, const u32 b) {
	u256 Result = a.Value >> b;
	return Result;
}
