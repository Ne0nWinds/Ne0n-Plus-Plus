/* == v2 == */
MATHCALL v2 operator+(const v2 &a, const v2 &b) {
	v2 Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	return Result;
}
MATHCALL void operator+=(v2 &a, const v2 &b) {
	a = a + b;
}

MATHCALL v2 operator-(const v2 &a, const v2 &b) {
	v2 Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	return Result;
}
MATHCALL void operator-=(v2 &a, const v2 &b) {
	a = a - b;
}

MATHCALL v2 operator*(const v2 &a, const v2 &b) {
	v2 Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	return Result;
}
MATHCALL void operator*=(v2 &a, const v2 &b) {
	a = a * b;
}

MATHCALL v2 operator/(const v2 &a, const v2 &b) {
	v2 Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	return Result;
}
MATHCALL void operator/=(v2 &a, const v2 &b) {
	a = a / b;
}

MATHCALL v2 operator&(const v2 &a, const u32x2 &b) {
	v2 Result;
	*(u32 *)&Result.x = *(u32 *)&a.x & b.x;
	*(u32 *)&Result.y = *(u32 *)&a.y & b.y;
	return Result;
}
MATHCALL void operator&=(v2 &a, const u32x2 &b) {
	a = a & b;
}

/* == v3 == */
MATHCALL v3 operator+(const v3 &a, const v3 &b) {
	v3 Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	return Result;
}
MATHCALL void operator+=(v3 &a, const v3 &b) {
	a = a + b;
}
MATHCALL v3 operator-(const v3 &a, const v3 &b) {
	v3 Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	Result.z = a.z - b.z;
	return Result;
}
MATHCALL void operator-=(v3 &a, const v3 &b) {
	a = a - b;
}
MATHCALL v3 operator*(const v3 &a, const v3 &b) {
	v3 Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	Result.z = a.z * b.z;
	return Result;
}
MATHCALL void operator*=(v3 &a, const v3 &b) {
	a = a * b;
}
MATHCALL v3 operator/(const v3 &a, const v3 &b) {
	v3 Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	Result.z = a.z / b.z;
	return Result;
}
MATHCALL void operator/=(v3 &a, const v3 &b) {
	a = a / b;
}

MATHCALL v3 operator&(const v3 &a, const u32x3 &b) {
	v3 Result;
	*(u32 *)&Result.x = *(u32 *)&a.x & b.x;
	*(u32 *)&Result.y = *(u32 *)&a.y & b.y;
	*(u32 *)&Result.z = *(u32 *)&a.z & b.z;
	return Result;
}
MATHCALL void operator&=(v3 &a, const u32x3 &b) {
	a = a & b;
}

/* == v4 == */
MATHCALL v4 operator+(const v4 &a, const v4 &b) {
	v4 Result;
	Result.x = a.x + b.x;
	Result.y = a.y + b.y;
	Result.z = a.z + b.z;
	Result.w = a.w + b.w;
	return Result;
}
MATHCALL void operator+=(v4 &a, const v4 &b) {
	a = a + b;
}
MATHCALL v4 operator-(const v4 &a, const v4 &b) {
	v4 Result;
	Result.x = a.x - b.x;
	Result.y = a.y - b.y;
	Result.z = a.z - b.z;
	Result.w = a.w - b.w;
	return Result;
}
MATHCALL void operator-=(v4 &a, const v4 &b) {
	a = a - b;
}
MATHCALL v4 operator*(const v4 &a, const v4 &b) {
	v4 Result;
	Result.x = a.x * b.x;
	Result.y = a.y * b.y;
	Result.z = a.z * b.z;
	Result.w = a.w * b.w;
	return Result;
}
MATHCALL void operator*=(v4 &a, const v4 &b) {
	a = a * b;
}
MATHCALL v4 operator/(const v4 &a, const v4 &b) {
	v4 Result;
	Result.x = a.x / b.x;
	Result.y = a.y / b.y;
	Result.z = a.z / b.z;
	Result.w = a.w / b.w;
	return Result;
}
MATHCALL void operator/=(v4 &a, const v4 &b) {
	a = a / b;
}

MATHCALL v8 operator+(const v8 &a, const v8 &b) {
	v8 Result = a;
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
	a[4] += b[4];
	a[5] += b[5];
	a[6] += b[6];
	a[7] += b[7];
	return Result;
}
MATHCALL void operator+=(v8 &a, const v8 &b) {
	a = a + b;
}
MATHCALL v8 operator-(const v8 &a, const v8 &b) {
	v8 Result = a;
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] -= b[3];
	a[4] -= b[4];
	a[5] -= b[5];
	a[6] -= b[6];
	a[7] -= b[7];
	return Result;
}
MATHCALL void operator-=(v8 &a, const v8 &b) {
	a = a - b;
}
MATHCALL v8 operator*(const v8 &a, const v8 &b) {
	v8 Result = a;
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] *= b[3];
	a[4] *= b[4];
	a[5] *= b[5];
	a[6] *= b[6];
	a[7] *= b[7];
	return Result;
}
MATHCALL void operator*=(v8 &a, const v8 &b) {
	a = a * b;
}
MATHCALL v8 operator/(const v8 &a, const v8 &b) {
	v8 Result = a;
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] /= b[3];
	a[4] /= b[4];
	a[5] /= b[5];
	a[6] /= b[6];
	a[7] /= b[7];
	return Result;
}
MATHCALL void operator/=(v8 &a, const v8 &b) {
	a = a / b;
}
MATHCALL v4 operator&(const v4 &a, const u32x4 &b) {
	v4 Result;
	*(u32 *)&Result.x = *(u32 *)&a.x & b.x;
	*(u32 *)&Result.y = *(u32 *)&a.y & b.y;
	*(u32 *)&Result.z = *(u32 *)&a.z & b.z;
	*(u32 *)&Result.w = *(u32 *)&a.w & b.w;
	return Result;
}
MATHCALL void operator&=(v4 &a, const u32x4 &b) {
	a = a & b;
}
