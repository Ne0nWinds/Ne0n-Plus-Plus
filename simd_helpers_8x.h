struct u32x {
	u32x8 Value;

	force_inline constexpr u32x() : Value((u32)0) { }
	force_inline constexpr u32x(u32 n) : Value(n) { }
};

struct f32x {
	v8 Value;

	force_inline constexpr f32x() : Value((f32)0) { }
	force_inline constexpr f32x(f32 n) : Value(n) { }
	force_inline constexpr f32x(v8 n) : Value(n) { }
};
