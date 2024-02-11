MATHCALL f32x operator+(const f32x &a, const f32x &b) {
	f32x Result = a.Value + b.Value;
	return Result;
}
MATHCALL f32x operator-(const f32x &a, const f32x &b) {
	f32x Result = a.Value - b.Value;
	return Result;
}
MATHCALL f32x operator*(const f32x &a, const f32x &b) {
	f32x Result = a.Value * b.Value;
	return Result;
}
MATHCALL f32x operator/(const f32x &a, const f32x &b) {
	f32x Result = a.Value / b.Value;
	return Result;
}

struct v2x {
	f32x x, y;

	force_inline constexpr v2x() : x(0), y(0) { }
	force_inline constexpr v2x(f32 n) : x(n), y(n) { }
	force_inline constexpr v2x(v2 a) : x(a.x), y(a.y) { }
};

MATHCALL v2x operator+(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	return Result;
}
MATHCALL v2x operator-(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	return Result;
}
MATHCALL v2x operator*(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	return Result;
}
MATHCALL v2x operator/(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	return Result;
}

struct v3x {
	f32x x, y, z;

	force_inline constexpr v3x() : x(0), y(0), z(0) { }
	force_inline constexpr v3x(f32 n) : x(n), y(n), z(n) { }
	force_inline constexpr v3x(v3 a) : x(a.x), y(a.y), z(a.z) { }
};

MATHCALL v3x operator+(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	return Result;
}
MATHCALL v3x operator-(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	Result.z = a.z - b.z;
	return Result;
}
MATHCALL v3x operator*(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	Result.z = a.z * b.z;
	return Result;
}
MATHCALL v3x operator/(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	Result.z = a.z / b.z;
	return Result;
}

struct v4x {
	f32x x, y, z, w;

	force_inline constexpr v4x() : x(0), y(0), z(0), w(0) { }
	force_inline constexpr v4x(f32 n) : x(n), y(n), z(n), w(n) { }
	force_inline constexpr v4x(v4 a) : x(a.x), y(a.y), z(a.z), w(a.w) { }
};

MATHCALL v4x operator+(const v4x &a, const v4x &b) {
	v4x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	Result.w = a.w + b.w;
	return Result;
}
MATHCALL v4x operator-(const v4x &a, const v4x &b) {
	v4x Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	Result.z = a.z - b.z;
	Result.w = a.w - b.w;
	return Result;
}
MATHCALL v4x operator*(const v4x &a, const v4x &b) {
	v4x Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	Result.z = a.z * b.z;
	Result.w = a.w * b.w;
	return Result;
}
MATHCALL v4x operator/(const v4x &a, const v4x &b) {
	v4x Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	Result.z = a.z / b.z;
	Result.w = a.w / b.w;
	return Result;
}

struct u128 {
	u64 Value[2];

	force_inline constexpr u128() : Value { 0, 0 } { }
};
