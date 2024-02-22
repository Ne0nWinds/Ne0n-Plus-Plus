struct v2x {
	f32x x, y;

	force_inline constexpr v2x() : x(0), y(0) { }
	force_inline constexpr v2x(f32 n) : x(n), y(n) { }
	force_inline constexpr v2x(v2 a) : x(a.x), y(a.y) { }
};

struct v3x {
	f32x x, y, z;

	force_inline constexpr v3x() : x(0), y(0), z(0) { }
	force_inline constexpr v3x(f32 n) : x(n), y(n), z(n) { }
	force_inline constexpr v3x(v3 a) : x(a.x), y(a.y), z(a.z) { }
};

struct v4x {
	f32x x, y, z, w;

	force_inline constexpr v4x() : x(0), y(0), z(0), w(0) { }
	force_inline constexpr v4x(f32 n) : x(n), y(n), z(n), w(n) { }
	force_inline constexpr v4x(v4 a) : x(a.x), y(a.y), z(a.z), w(a.w) { }
};

MATHCALL f32x operator+(const f32x &a, const f32x &b) {
	f32x Result;
	Result.Value = a.Value + b.Value;
	return Result;
}
MATHCALL v2x operator+(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	return Result;
}
MATHCALL v3x operator+(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	return Result;
}
MATHCALL v4x operator+(const v4x &a, const v4x &b) {
	v4x Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	Result.w = a.w + b.w;
	return Result;
}
MATHCALL u32x operator+(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value + b.Value;
	return Result;
}

MATHCALL f32x operator-(const f32x &a, const f32x &b) {
	f32x Result;
	Result.Value = a.Value - b.Value;
	return Result;
}
MATHCALL v2x operator-(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	return Result;
}
MATHCALL v3x operator-(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	Result.z = a.z - b.z;
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
MATHCALL u32x operator-(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value - b.Value;
	return Result;
}

MATHCALL f32x operator*(const f32x &a, const f32x &b) {
	f32x Result = a.Value * b.Value;
	return Result;
}
MATHCALL v2x operator*(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	return Result;
}
MATHCALL v3x operator*(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	Result.z = a.z * b.z;
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
MATHCALL u32x operator*(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value * b.Value;
	return Result;
}

MATHCALL f32x operator/(const f32x &a, const f32x &b) {
	f32x Result = a.Value / b.Value;
	return Result;
}
MATHCALL v2x operator/(const v2x &a, const v2x &b) {
	v2x Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	return Result;
}
MATHCALL v3x operator/(const v3x &a, const v3x &b) {
	v3x Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	Result.z = a.z / b.z;
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
MATHCALL u32x operator/(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value / b.Value;
	return Result;
}

MATHCALL f32x operator-(const f32x &a) {
	f32x Result = a ^ u32x(SignBit);
	return Result;
}
MATHCALL v2x operator-(const v2x &a) {
	v2x Result = a ^ u32x(SignBit);
	return Result;
}
MATHCALL v3x operator-(const v3x &a) {
	v3x Result = a ^ u32x(SignBit);
	return Result;
}
MATHCALL v4x operator-(const v4x &a) {
	v4x Result = a ^ u32x(SignBit);
	return Result;
}
MATHCALL u32x operator-(const u32x &a) {
	u32x Result = a;
	Result.Value = ~Result.Value + 1;
	return Result;
}

MATHCALL u32x operator==(const f32x &a, const f32x &b) {
	u32x Result;
	Result.Value = a.Value == b.Value;
	return Result;
}
MATHCALL u32x operator==(const v2x &a, const v2x &b) {
	u32x Result = (a.x == b.x) & (a.y == a.y);
	return Result;
}
MATHCALL u32x operator==(const v3x &a, const v3x &b) {
	u32x Result = (a.x == b.x) & (a.y == a.y) & (a.z == a.z);
	return Result;
}
MATHCALL u32x operator==(const v4x &a, const v4x &b) {
	u32x Result = (a.x == b.x) & (a.y == a.y) & (a.z == a.z) & (a.w == a.w);
	return Result;
}
MATHCALL u32x operator==(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value == b.Value;
	return Result;
}

MATHCALL u32x operator!=(const f32x &a, const f32x &b) {
	u32x Result;
	Result.Value = a.Value != b.Value;
	return Result;
}
MATHCALL u32x operator!=(const v2x &a, const v2x &b) {
	u32x Result = (a.x != b.x) | (a.y != a.y);
	return Result;
}
MATHCALL u32x operator!=(const v3x &a, const v3x &b) {
	u32x Result = (a.x != b.x) | (a.y != a.y) | (a.z != a.z);
	return Result;
}
MATHCALL u32x operator!=(const v4x &a, const v4x &b) {
	u32x Result = (a.x != b.x) | (a.y != a.y) | (a.z != a.z) | (a.w != a.w);
	return Result;
}
MATHCALL u32x operator!=(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value != b.Value;
	return Result;
}

MATHCALL u32x operator>(const f32x &a, const f32x &b) {
	u32x Result;
	Result.Value = a.Value > b.Value;
	return Result;
}
MATHCALL u32x operator>(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value > b.Value;
	return Result;
}

MATHCALL u32x operator<(const f32x &a, const f32x &b) {
	u32x Result;
	Result.Value = a.Value < b.Value;
	return Result;
}
MATHCALL u32x operator<(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value < b.Value;
	return Result;
}

MATHCALL f32x operator&(const f32x &a, const u32x &b) {
	f32x Result;
	Result.Value = a.Value & b.Value;
	return Result;
}
MATHCALL v2x operator&(const v2x &a, const u32x &b) {
	v2x Result;
	Result.x = Result.x & b;
	Result.y = Result.y & b;
	return Result;
}
MATHCALL v3x operator&(const v3x &a, const u32x &b) {
	v3x Result;
	Result.x = Result.x & b;
	Result.y = Result.y & b;
	Result.z = Result.z & b;
	return Result;
}
MATHCALL v4x operator&(const v4x &a, const u32x &b) {
	v4x Result;
	Result.x = Result.x & b;
	Result.y = Result.y & b;
	Result.z = Result.z & b;
	Result.w = Result.w & b;
	return Result;
}
MATHCALL u32x operator&(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value & b.Value;
	return Result;
}

MATHCALL f32x operator|(const f32x &a, const u32x &b) {
	f32x Result;
	Result.Value = a.Value | b.Value;
	return Result;
}
MATHCALL v2x operator|(const v2x &a, const u32x &b) {
	v2x Result;
	Result.x = Result.x | b;
	Result.y = Result.y | b;
	return Result;
}
MATHCALL v3x operator|(const v3x &a, const u32x &b) {
	v3x Result;
	Result.x = Result.x | b;
	Result.y = Result.y | b;
	Result.z = Result.z | b;
	return Result;
}
MATHCALL v4x operator|(const v4x &a, const u32x &b) {
	v4x Result;
	Result.x = Result.x | b;
	Result.y = Result.y | b;
	Result.z = Result.z | b;
	Result.w = Result.w | b;
	return Result;
}
MATHCALL u32x operator|(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value | b.Value;
	return Result;
}

MATHCALL f32x operator^(const f32x &a, const u32x &b) {
	f32x Result;
	Result.Value = a.Value ^ b.Value;
	return Result;
}
MATHCALL v2x operator^(const v2x &a, const u32x &b) {
	v2x Result;
	Result.x = Result.x ^ b;
	Result.y = Result.y ^ b;
	return Result;
}
MATHCALL v3x operator^(const v3x &a, const u32x &b) {
	v3x Result;
	Result.x = Result.x ^ b;
	Result.y = Result.y ^ b;
	Result.z = Result.z ^ b;
	return Result;
}
MATHCALL v4x operator^(const v4x &a, const u32x &b) {
	v4x Result;
	Result.x = Result.x ^ b;
	Result.y = Result.y ^ b;
	Result.z = Result.z ^ b;
	Result.w = Result.w ^ b;
	return Result;
}
MATHCALL u32x operator^(const u32x &a, const u32x &b) {
	u32x Result;
	Result.Value = a.Value ^ b.Value;
	return Result;
}

MATHCALL f32x operator<<(const f32x &a, const u32 b) {
	f32x Result;
	Result.Value = a.Value << b;
	return Result;
}
MATHCALL v2x operator<<(const v2x &a, const u32 b) {
	v2x Result;
	Result.x = Result.x << b;
	Result.y = Result.y << b;
	return Result;
}
MATHCALL v3x operator<<(const v3x &a, const u32 b) {
	v3x Result;
	Result.x = Result.x << b;
	Result.y = Result.y << b;
	Result.z = Result.z << b;
	return Result;
}
MATHCALL v4x operator<<(const v4x &a, const u32 b) {
	v4x Result;
	Result.x = Result.x << b;
	Result.y = Result.y << b;
	Result.z = Result.z << b;
	Result.w = Result.w << b;
	return Result;
}
MATHCALL u32x operator<<(const u32x &a, const u32 b) {
	u32x Result;
	Result.Value = a.Value << b;
	return Result;
}

MATHCALL f32x operator>>(const f32x &a, const u32 b) {
	f32x Result;
	Result.Value = a.Value >> b;
	return Result;
}
MATHCALL v2x operator>>(const v2x &a, const u32 b) {
	v2x Result;
	Result.x = Result.x >> b;
	Result.y = Result.y >> b;
	return Result;
}
MATHCALL v3x operator>>(const v3x &a, const u32 b) {
	v3x Result;
	Result.x = Result.x >> b;
	Result.y = Result.y >> b;
	Result.z = Result.z >> b;
	return Result;
}
MATHCALL v4x operator>>(const v4x &a, const u32 b) {
	v4x Result;
	Result.x = Result.x >> b;
	Result.y = Result.y >> b;
	Result.z = Result.z >> b;
	Result.w = Result.w >> b;
	return Result;
}
MATHCALL u32x operator>>(const u32x &a, const u32 b) {
	u32x Result;
	Result.Value = a.Value >> b;
	return Result;
}

MATHCALL void operator+=(f32x &a, const f32x &b) { a = a + b; }
MATHCALL void operator+=(v2x &a, const v2x &b) { a = a + b; }
MATHCALL void operator+=(v3x &a, const v3x &b) { a = a + b; }
MATHCALL void operator+=(v4x &a, const v4x &b) { a = a + b; }
MATHCALL void operator+=(u32x &a, const u32x &b) { a = a + b; }

MATHCALL void operator-=(f32x &a, const f32x &b) { a = a - b; }
MATHCALL void operator-=(v2x &a, const v2x &b) { a = a - b; }
MATHCALL void operator-=(v3x &a, const v3x &b) { a = a - b; }
MATHCALL void operator-=(v4x &a, const v4x &b) { a = a - b; }
MATHCALL void operator-=(u32x &a, const u32x &b) { a = a - b; }

MATHCALL void operator*=(f32x &a, const f32x &b) { a = a * b; }
MATHCALL void operator*=(v3x &a, const v3x &b) { a = a * b; }
MATHCALL void operator*=(v2x &a, const v2x &b) { a = a * b; }
MATHCALL void operator*=(v4x &a, const v4x &b) { a = a * b; }
MATHCALL void operator*=(u32x &a, const u32x &b) { a = a * b; }

MATHCALL void operator/=(f32x &a, const f32x &b) { a = a / b; }
MATHCALL void operator/=(v2x &a, const v2x &b) { a = a / b; }
MATHCALL void operator/=(v3x &a, const v3x &b) { a = a / b; }
MATHCALL void operator/=(v4x &a, const v4x &b) { a = a / b; }
MATHCALL void operator/=(u32x &a, const u32x &b) { a = a / b; }

MATHCALL void operator&=(f32x &a, const u32x &b) { a = a & b; }
MATHCALL void operator&=(v2x &a, const u32x &b) { a = a & b; }
MATHCALL void operator&=(v3x &a, const u32x &b) { a = a & b; }
MATHCALL void operator&=(v4x &a, const u32x &b) { a = a & b; }
MATHCALL void operator&=(u32x &a, const u32x &b) { a = a & b; }

MATHCALL void operator|=(f32x &a, const u32x &b) { a = a | b; }
MATHCALL void operator|=(v2x &a, const u32x &b) { a = a | b; }
MATHCALL void operator|=(v3x &a, const u32x &b) { a = a | b; }
MATHCALL void operator|=(v4x &a, const u32x &b) { a = a | b; }
MATHCALL void operator|=(u32x &a, const u32x &b) { a = a | b; }

MATHCALL void operator^=(f32x &a, const u32x &b) { a = a ^ b; }
MATHCALL void operator^=(v2x &a, const u32x &b) { a = a ^ b; }
MATHCALL void operator^=(v3x &a, const u32x &b) { a = a ^ b; }
MATHCALL void operator^=(v4x &a, const u32x &b) { a = a ^ b; }
MATHCALL void operator^=(u32x &a, const u32x &b) { a = a ^ b; }

MATHCALL void operator<<=(f32x &a, const u32 b) { a = a << b; }
MATHCALL void operator<<=(v2x &a, const u32 b) { a = a << b; }
MATHCALL void operator<<=(v3x &a, const u32 b) { a = a << b; }
MATHCALL void operator<<=(v4x &a, const u32 b) { a = a << b; }
MATHCALL void operator<<=(u32x &a, const u32 b) { a = a << b; }

MATHCALL void operator>>=(f32x &a, const u32 b) { a = a >> b; }
MATHCALL void operator>>=(v2x &a, const u32 b) { a = a >> b; }
MATHCALL void operator>>=(v3x &a, const u32 b) { a = a >> b; }
MATHCALL void operator>>=(v4x &a, const u32 b) { a = a >> b; }
MATHCALL void operator>>=(u32x &a, const u32 b) { a = a >> b; }

MATHCALL u32x operator<=(const f32x &a, const f32x &b) { return (a < b) | (a == b); }
MATHCALL u32x operator<=(const u32x &a, const u32x &b) { return (a < b) | (a == b); }

MATHCALL u32x operator>=(const f32x &a, const f32x &b) { return (a > b) | (a == b); }
MATHCALL u32x operator>=(const u32x &a, const u32x &b) { return (a > b) | (a == b); }

