
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
