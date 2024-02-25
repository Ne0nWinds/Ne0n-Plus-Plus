
struct alignas(8) v2 {
	f32 x, y;

	force_inline constexpr v2() : x(0.0f), y(0.0f) { }
	force_inline constexpr v2(f32 n) : x(n), y(n) { }
	force_inline constexpr v2(f32 _x, f32 _y) : x(_x), y(_y) { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 2);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

struct alignas(16) v3 {
	f32 x, y, z;

	force_inline constexpr v3() : x(0.0f), y(0.0f), z(0.0f) { }
	force_inline constexpr v3(f32 n) : x(n), y(n), z(n) { }
	force_inline constexpr v3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) { }
	explicit force_inline constexpr v3(const v2& a) : x(a.x), y(a.y), z(0.0f) { }
	force_inline constexpr v3(const v2& a, f32 b) : x(a.x), y(a.y), z(b) { }
	force_inline constexpr v3(f32 a, const v2& b) : x(a), y(b.x), z(b.y) { }

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 3);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

struct alignas(16) v4 {
	f32 x, y, z, w;

	force_inline constexpr v4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
	force_inline constexpr v4(f32 n) : x(n), y(n), z(n), w(n) { }
	force_inline constexpr v4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) { }
	explicit force_inline constexpr v4(const v2& a) : x(a.x), y(a.y), z(0.0f), w(0.0f) { }
	explicit force_inline constexpr v4(const v3& a) : x(a.x), y(a.y), z(a.z), w(0.0f) { }
	force_inline constexpr v4(const v2& a, f32 b, f32 c) : x(a.x), y(a.y), z(b), w(c) { }
	force_inline constexpr v4(const v2& a, const v2& b) : x(a.x), y(a.y), z(b.x), w(b.y) { }
	force_inline constexpr v4(const v3& a, f32 b) : x(a.x), y(a.y), z(a.z), w(b) { }
	force_inline constexpr v4(f32 a, const v3& b) : x(a), y(b.x), z(b.y), w(b.z) { }

	inline constexpr f32 operator[](u32 Index) const {
		Assert(Index < 3);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < 3);
		f32 *Array = (f32 *)this;
		return Array[Index];
	}
};

struct alignas(32) v8 {
	union {
		struct { f32 x, y, z, w; };
		f32 Data[8];
		v4 V4[2];
	};

	force_inline constexpr v8() : Data {0.0f} { }
	force_inline constexpr v8(f32 n) : Data {n,n,n,n,n,n,n,n} { }
	force_inline constexpr v8(v4 a, v4 b) : V4 { a, b } { }

	inline constexpr f32 operator[](u32 Index) const {
		Assert(Index < array_len(Data));
		const f32 Result = Data[Index];
		return Result;
	}

	inline constexpr f32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

struct alignas(8) u32x2 {
	union {
		struct { u32 x, y; };
		u32 Data[2];
		u64 _u64;
	};

	force_inline constexpr u32x2() : x(0), y(0) { }
	force_inline constexpr u32x2(u32 n) : x(n), y(n) { }
	explicit force_inline constexpr u32x2(bool n) : _u64(~(u64)n + 1) { }
	force_inline constexpr u32x2(u32 _x, u32 _y) : x(_x), y(_y) { }

	inline constexpr u32 operator[](u32 Index) const {
		Assert(Index < array_len(Data));
		return Data[Index];
	}

	inline constexpr u32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

struct alignas(16) u32x3 {
	union {
		struct { u32 x, y, z; };
		u32 Data[4];
		u64 _u64[2];
	};
	force_inline constexpr u32x3() : _u64 { 0 } { }
	force_inline constexpr u32x3(u32 n) : Data { n, n, n, n } { }
	explicit force_inline constexpr u32x3(u32x2 a) : x(a.x), y(a.y), z(0) { }
	force_inline constexpr u32x3(u32x2 a, u32 b) : x(a.x), y(a.y), z(b) { }
	explicit force_inline constexpr u32x3(bool n) : _u64 { ~(u64)n + 1, ~(u64)n + 1 } { }
	force_inline constexpr u32x3(u32 _x, u32 _y, u32 _z) : x(_x), y(_y), z(_z) { }

	inline constexpr u32 operator[](u32 Index) const {
		Assert(Index < array_len(Data));
		return Data[Index];
	}

	inline constexpr u32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

struct alignas(16) u32x4 {
	union {
		struct { u32 x, y, z, w; };
		u32 Data[4];
		u64 _u64[2];
	};
	force_inline constexpr u32x4() : _u64 { 0 } { }
	force_inline constexpr u32x4(u32 n) : Data { n, n, n, n } { }
	explicit force_inline constexpr u32x4(u32x2 n) : x(n.x), y(n.y), z(0), w(0) { }
	explicit force_inline constexpr u32x4(u32x3 n) : x(n.x), y(n.y), z(n.z), w(0) { }
	explicit force_inline constexpr u32x4(bool n) : _u64 { ~(u64)n + 1, ~(u64)n + 1 } { }
	force_inline constexpr u32x4(u32 _x, u32 _y, u32 _z, u32 _w) : x(_x), y(_y), z(_z), w(_z) { }

	inline constexpr u32 operator[](u32 Index) const {
		Assert(Index < array_len(Data));
		return Data[Index];
	}

	inline constexpr u32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

struct alignas(32) u32x8 {
	union {
		struct { u32 x, y, z, w; };
		u32 Data[8];
		u64 _u64[4];
		u32x4 U32x4[2];
	};
	force_inline constexpr u32x8() : _u64 { 0 } { }
	force_inline constexpr u32x8(u32 n) : Data { n, n, n, n, n, n, n, n } { }
	force_inline constexpr u32x8(u32x4 a, u32x4 b) : U32x4 { a, b } { }
	explicit force_inline constexpr u32x8(u32x2 n) : x(n.x), y(n.y), z(0), w(0) { }
	explicit force_inline constexpr u32x8(u32x3 n) : x(n.x), y(n.y), z(n.z), w(0) { }
	explicit force_inline constexpr u32x8(u32x4 n) : x(n.x), y(n.y), z(n.z), w(n.w) { }
	explicit force_inline constexpr u32x8(bool n) : U32x4 { ~(u32)n + 1, ~(u32)n + 1 } { }

	inline constexpr u32 operator[](u32 Index) const {
		Assert(Index < array_len(Data));
		return Data[Index];
	}

	inline constexpr u32 &operator[](u32 Index) {
		Assert(Index < array_len(Data));
		return Data[Index];
	}
};

#define define_operators(type1, type2) \
MATHCALL type1 operator+(const type1 &a, const type1 &b);\
MATHCALL type1 operator-(const type1 &a, const type1 &b);\
MATHCALL type1 operator*(const type1 &a, const type1 &b);\
MATHCALL type1 operator/(const type1 &a, const type1 &b);\
MATHCALL type1 operator-(const type1 &a);\
MATHCALL type2 operator==(const type1 &a, const type1 &b);\
MATHCALL type2 operator!=(const type1 &a, const type1 &b);\
MATHCALL type2 operator>(const type1 &a, const type1 &b);\
MATHCALL type2 operator<(const type1 &a, const type1 &b);\
MATHCALL type1 operator&(const type1 &a, const type2 &b);\
MATHCALL type1 operator|(const type1 &a, const type2 &b);\
MATHCALL type1 operator^(const type1 &a, const type2 &b);\
MATHCALL type1 operator~(const type1 &a);\
MATHCALL type1 operator<<(const type1 &a, const u32 &b);\
MATHCALL type1 operator>>(const type1 &a, const u32 &b);\
MATHCALL void operator+=(type1 &a, const type1 &b) { a = a + b; }\
MATHCALL void operator-=(type1 &a, const type1 &b) { a = a - b; }\
MATHCALL void operator*=(type1 &a, const type1 &b) { a = a * b; }\
MATHCALL void operator/=(type1 &a, const type1 &b) { a = a / b; }\
MATHCALL void operator&=(type1 &a, const type2 &b) { a = a & b; }\
MATHCALL void operator|=(type1 &a, const type2 &b) { a = a | b; }\
MATHCALL void operator^=(type1 &a, const type2 &b) { a = a ^ b; }\
MATHCALL void operator<<=(type1 &a, const u32 &b) { a = a << b; }\
MATHCALL void operator>>=(type1 &a, const u32 &b) { a = a >> b; }\
MATHCALL type2 operator<=(const type1 &a, const type1 &b) { return (a < b) | (a == b); }\
MATHCALL type2 operator>=(const type1 &a, const type1 &b) { return (a > b) | (a == b); }

define_operators(u32x2, u32x2)
define_operators(u32x3, u32x3)
define_operators(u32x4, u32x4)
define_operators(u32x8, u32x8)
define_operators(v2, u32x2)
define_operators(v3, u32x3)
define_operators(v4, u32x4)
define_operators(v8, u32x8)
