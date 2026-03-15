#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "core_string.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(value, min, max) (((value) < (min)) ? (min) : (((value) > (max)) ? (max) : (value)))

#define F32_EPSILON 1.1920928955078125e-7f
#define F64_EPSILON 2.2204460492503131e-16

#define F32_PI 3.14159265358979323846f
#define F32_TAU 6.28318530717958647692f

typedef struct Vec2
{
    f32 x;
    f32 y;
} Vec2;

typedef struct Vec3
{
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Vec4
{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Mat2
{
    f32 elements[2][2];
} Mat2;

typedef struct Mat3
{
    f32 elements[3][3];
} Mat3;

typedef struct Mat4
{
    f32 elements[4][4];
} Mat4;

typedef struct IVec2
{
    i32 x;
    i32 y;
} IVec2;

typedef struct Rect2
{
    Vec2 min;
    Vec2 max;
} Rect2;

typedef struct RangeUsize
{
    usize min;
    usize max;
} RangeUsize;

typedef struct SpanF32
{
    f32 *values;
    usize count;
} SpanF32;

typedef struct SpanF64
{
    f64 *values;
    usize count;
} SpanF64;

f32 F32_Abs (f32 value);
f32 F32_Min (f32 a, f32 b);
f32 F32_Max (f32 a, f32 b);
f32 F32_Clamp (f32 value, f32 min, f32 max);
f32 F32_Lerp (f32 a, f32 b, f32 t);
f32 F32_Sign (f32 value);
f32 F32_Sqrt (f32 value);
f32 F32_Exp (f32 value);
f32 F32_Log (f32 value);
f32 F32_Pow (f32 base, f32 exponent);
f32 F32_Floor (f32 value);
f32 F32_Ceil (f32 value);
f32 F32_Round (f32 value);
f32 F32_Mod (f32 numerator, f32 denominator);
f32 F32_Sin (f32 radians);
f32 F32_Cos (f32 radians);
f32 F32_Tan (f32 radians);
f32 F32_Tanh (f32 value);
f32 F32_Asin (f32 value);
f32 F32_Acos (f32 value);
f32 F32_Atan2 (f32 y, f32 x);
b32 F32_IsNan (f32 value);
b32 F32_IsFinite (f32 value);
b32 F32_ApproxEqual (f32 a, f32 b, f32 epsilon);

f64 F64_Abs (f64 value);
f64 F64_Min (f64 a, f64 b);
f64 F64_Max (f64 a, f64 b);
f64 F64_Clamp (f64 value, f64 min, f64 max);
f64 F64_Lerp (f64 a, f64 b, f64 t);
f64 F64_Sign (f64 value);
f64 F64_Sqrt (f64 value);
f64 F64_Exp (f64 value);
f64 F64_Log (f64 value);
f64 F64_Pow (f64 base, f64 exponent);
f64 F64_Floor (f64 value);
f64 F64_Ceil (f64 value);
f64 F64_Round (f64 value);
f64 F64_Mod (f64 numerator, f64 denominator);
f64 F64_Sin (f64 radians);
f64 F64_Cos (f64 radians);
f64 F64_Tan (f64 radians);
f64 F64_Tanh (f64 value);
f64 F64_Asin (f64 value);
f64 F64_Acos (f64 value);
f64 F64_Atan2 (f64 y, f64 x);
b32 F64_IsNan (f64 value);
b32 F64_IsFinite (f64 value);
b32 F64_ApproxEqual (f64 a, f64 b, f64 epsilon);

i32 I32_Abs (i32 value);
i32 I32_Min (i32 a, i32 b);
i32 I32_Max (i32 a, i32 b);
i32 I32_Clamp (i32 value, i32 min, i32 max);

Vec2 Vec2_Create (f32 x, f32 y);
Vec2 Vec2_Add (Vec2 a, Vec2 b);
Vec2 Vec2_Subtract (Vec2 a, Vec2 b);
Vec2 Vec2_Scale (Vec2 value, f32 scalar);
Vec2 Vec2_HadamardMultiply (Vec2 a, Vec2 b);
f32 Vec2_Dot (Vec2 a, Vec2 b);
f32 Vec2_LengthSquared (Vec2 value);
f32 Vec2_Length (Vec2 value);
Vec2 Vec2_Normalize (Vec2 value);
f32 Vec2_DistanceSquared (Vec2 a, Vec2 b);
f32 Vec2_Distance (Vec2 a, Vec2 b);

Vec3 Vec3_Create (f32 x, f32 y, f32 z);
Vec3 Vec3_Add (Vec3 a, Vec3 b);
Vec3 Vec3_Subtract (Vec3 a, Vec3 b);
Vec3 Vec3_Scale (Vec3 value, f32 scalar);
Vec3 Vec3_HadamardMultiply (Vec3 a, Vec3 b);
f32 Vec3_Dot (Vec3 a, Vec3 b);
Vec3 Vec3_Cross (Vec3 a, Vec3 b);
f32 Vec3_LengthSquared (Vec3 value);
f32 Vec3_Length (Vec3 value);
Vec3 Vec3_Normalize (Vec3 value);
f32 Vec3_DistanceSquared (Vec3 a, Vec3 b);
f32 Vec3_Distance (Vec3 a, Vec3 b);

Vec4 Vec4_Create (f32 x, f32 y, f32 z, f32 w);
Vec4 Vec4_Add (Vec4 a, Vec4 b);
Vec4 Vec4_Subtract (Vec4 a, Vec4 b);
Vec4 Vec4_Scale (Vec4 value, f32 scalar);
Vec4 Vec4_HadamardMultiply (Vec4 a, Vec4 b);
f32 Vec4_Dot (Vec4 a, Vec4 b);
f32 Vec4_LengthSquared (Vec4 value);
f32 Vec4_Length (Vec4 value);
Vec4 Vec4_Normalize (Vec4 value);

Mat2 Mat2_Create (f32 e00, f32 e01, f32 e10, f32 e11);
Mat2 Mat2_CreateIdentity (void);
Mat2 Mat2_Transpose (Mat2 matrix);
Mat2 Mat2_Multiply (Mat2 left, Mat2 right);
Vec2 Mat2_MultiplyVec2 (Mat2 matrix, Vec2 vector);

Mat3 Mat3_Create (
    f32 e00, f32 e01, f32 e02,
    f32 e10, f32 e11, f32 e12,
    f32 e20, f32 e21, f32 e22
);
Mat3 Mat3_CreateIdentity (void);
Mat3 Mat3_Transpose (Mat3 matrix);
Mat3 Mat3_Multiply (Mat3 left, Mat3 right);
Vec3 Mat3_MultiplyVec3 (Mat3 matrix, Vec3 vector);

Mat4 Mat4_Create (
    f32 e00, f32 e01, f32 e02, f32 e03,
    f32 e10, f32 e11, f32 e12, f32 e13,
    f32 e20, f32 e21, f32 e22, f32 e23,
    f32 e30, f32 e31, f32 e32, f32 e33
);
Mat4 Mat4_CreateIdentity (void);
Mat4 Mat4_Transpose (Mat4 matrix);
Mat4 Mat4_Multiply (Mat4 left, Mat4 right);
Vec4 Mat4_MultiplyVec4 (Mat4 matrix, Vec4 vector);

IVec2 IVec2_Create (i32 x, i32 y);
IVec2 IVec2_Add (IVec2 a, IVec2 b);
IVec2 IVec2_Subtract (IVec2 a, IVec2 b);

Rect2 Rect2_Create (f32 min_x, f32 min_y, f32 max_x, f32 max_y);
Rect2 Rect2_FromMinSize (Vec2 min, Vec2 size);
Vec2 Rect2_GetSize (Rect2 rect);
b32 Rect2_ContainsPoint (Rect2 rect, Vec2 point);
b32 Rect2_Intersects (Rect2 a, Rect2 b);

RangeUsize RangeUsize_Create (usize min, usize max);
usize RangeUsize_Count (RangeUsize range);
b32 RangeUsize_Contains (RangeUsize range, usize value);

SpanF32 SpanF32_Create (f32 *values, usize count);
f32 SpanF32_Sum (SpanF32 span);
f32 SpanF32_Mean (SpanF32 span);
f32 SpanF32_Min (SpanF32 span);
f32 SpanF32_Max (SpanF32 span);
usize SpanF32_ArgMin (SpanF32 span);
usize SpanF32_ArgMax (SpanF32 span);
f32 SpanF32_Variance (SpanF32 span);
f32 SpanF32_StandardDeviation (SpanF32 span);

SpanF64 SpanF64_Create (f64 *values, usize count);
f64 SpanF64_Sum (SpanF64 span);
f64 SpanF64_Mean (SpanF64 span);
f64 SpanF64_Min (SpanF64 span);
f64 SpanF64_Max (SpanF64 span);
usize SpanF64_ArgMin (SpanF64 span);
usize SpanF64_ArgMax (SpanF64 span);
f64 SpanF64_Variance (SpanF64 span);
f64 SpanF64_StandardDeviation (SpanF64 span);

#endif // CORE_MATH_H
