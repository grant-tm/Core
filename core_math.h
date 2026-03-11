#ifndef CORE_MATH_H
#define CORE_MATH_H

#include "core_string.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(value, min, max) (((value) < (min)) ? (min) : (((value) > (max)) ? (max) : (value)))

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

f32 F32_Abs (f32 value);
f32 F32_Min (f32 a, f32 b);
f32 F32_Max (f32 a, f32 b);
f32 F32_Clamp (f32 value, f32 min, f32 max);
f32 F32_Lerp (f32 a, f32 b, f32 t);
f32 F32_Sqrt (f32 value);
f32 F32_Sin (f32 radians);
f32 F32_Cos (f32 radians);
f32 F32_Tan (f32 radians);
f32 F32_Asin (f32 value);
f32 F32_Acos (f32 value);
f32 F32_Atan2 (f32 y, f32 x);

f64 F64_Abs (f64 value);
f64 F64_Sqrt (f64 value);
f64 F64_Sin (f64 radians);
f64 F64_Cos (f64 radians);
f64 F64_Tan (f64 radians);
f64 F64_Asin (f64 value);
f64 F64_Acos (f64 value);
f64 F64_Atan2 (f64 y, f64 x);

i32 I32_Abs (i32 value);
i32 I32_Min (i32 a, i32 b);
i32 I32_Max (i32 a, i32 b);
i32 I32_Clamp (i32 value, i32 min, i32 max);

Vec2 Vec2_Create (f32 x, f32 y);
Vec2 Vec2_Add (Vec2 a, Vec2 b);
Vec2 Vec2_Subtract (Vec2 a, Vec2 b);
Vec2 Vec2_Scale (Vec2 value, f32 scalar);
f32 Vec2_Dot (Vec2 a, Vec2 b);
f32 Vec2_LengthSquared (Vec2 value);

Vec3 Vec3_Create (f32 x, f32 y, f32 z);
Vec3 Vec3_Add (Vec3 a, Vec3 b);
Vec3 Vec3_Subtract (Vec3 a, Vec3 b);
Vec3 Vec3_Scale (Vec3 value, f32 scalar);
f32 Vec3_Dot (Vec3 a, Vec3 b);

Vec4 Vec4_Create (f32 x, f32 y, f32 z, f32 w);

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

#endif // CORE_MATH_H
