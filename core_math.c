#include <math.h>

#include "core_math.h"

f32 F32_Abs (f32 value)
{
    return (value < 0.0f) ? -value : value;
}

f32 F32_Min (f32 a, f32 b)
{
    return (a < b) ? a : b;
}

f32 F32_Max (f32 a, f32 b)
{
    return (a > b) ? a : b;
}

f32 F32_Clamp (f32 value, f32 min, f32 max)
{
    ASSERT(min <= max);

    return CLAMP(value, min, max);
}

f32 F32_Lerp (f32 a, f32 b, f32 t)
{
    return a + ((b - a) * t);
}

f32 F32_Sqrt (f32 value)
{
    ASSERT(value >= 0.0f);

    return sqrtf(value);
}

f32 F32_Sin (f32 radians)
{
    return sinf(radians);
}

f32 F32_Cos (f32 radians)
{
    return cosf(radians);
}

f32 F32_Tan (f32 radians)
{
    return tanf(radians);
}

f32 F32_Asin (f32 value)
{
    ASSERT((value >= -1.0f) && (value <= 1.0f));

    return asinf(value);
}

f32 F32_Acos (f32 value)
{
    ASSERT((value >= -1.0f) && (value <= 1.0f));

    return acosf(value);
}

f32 F32_Atan2 (f32 y, f32 x)
{
    return atan2f(y, x);
}

f64 F64_Abs (f64 value)
{
    return (value < 0.0) ? -value : value;
}

f64 F64_Sqrt (f64 value)
{
    ASSERT(value >= 0.0);

    return sqrt(value);
}

f64 F64_Sin (f64 radians)
{
    return sin(radians);
}

f64 F64_Cos (f64 radians)
{
    return cos(radians);
}

f64 F64_Tan (f64 radians)
{
    return tan(radians);
}

f64 F64_Asin (f64 value)
{
    ASSERT((value >= -1.0) && (value <= 1.0));

    return asin(value);
}

f64 F64_Acos (f64 value)
{
    ASSERT((value >= -1.0) && (value <= 1.0));

    return acos(value);
}

f64 F64_Atan2 (f64 y, f64 x)
{
    return atan2(y, x);
}

i32 I32_Abs (i32 value)
{
    return (value < 0) ? -value : value;
}

i32 I32_Min (i32 a, i32 b)
{
    return (a < b) ? a : b;
}

i32 I32_Max (i32 a, i32 b)
{
    return (a > b) ? a : b;
}

i32 I32_Clamp (i32 value, i32 min, i32 max)
{
    ASSERT(min <= max);

    return CLAMP(value, min, max);
}

Vec2 Vec2_Create (f32 x, f32 y)
{
    Vec2 result;

    result.x = x;
    result.y = y;
    return result;
}

Vec2 Vec2_Add (Vec2 a, Vec2 b)
{
    return Vec2_Create(a.x + b.x, a.y + b.y);
}

Vec2 Vec2_Subtract (Vec2 a, Vec2 b)
{
    return Vec2_Create(a.x - b.x, a.y - b.y);
}

Vec2 Vec2_Scale (Vec2 value, f32 scalar)
{
    return Vec2_Create(value.x * scalar, value.y * scalar);
}

f32 Vec2_Dot (Vec2 a, Vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

f32 Vec2_LengthSquared (Vec2 value)
{
    return Vec2_Dot(value, value);
}

Vec3 Vec3_Create (f32 x, f32 y, f32 z)
{
    Vec3 result;

    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Vec3 Vec3_Add (Vec3 a, Vec3 b)
{
    return Vec3_Create(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 Vec3_Subtract (Vec3 a, Vec3 b)
{
    return Vec3_Create(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 Vec3_Scale (Vec3 value, f32 scalar)
{
    return Vec3_Create(value.x * scalar, value.y * scalar, value.z * scalar);
}

f32 Vec3_Dot (Vec3 a, Vec3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec4 Vec4_Create (f32 x, f32 y, f32 z, f32 w)
{
    Vec4 result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
    return result;
}

IVec2 IVec2_Create (i32 x, i32 y)
{
    IVec2 result;

    result.x = x;
    result.y = y;
    return result;
}

IVec2 IVec2_Add (IVec2 a, IVec2 b)
{
    return IVec2_Create(a.x + b.x, a.y + b.y);
}

IVec2 IVec2_Subtract (IVec2 a, IVec2 b)
{
    return IVec2_Create(a.x - b.x, a.y - b.y);
}

Rect2 Rect2_Create (f32 min_x, f32 min_y, f32 max_x, f32 max_y)
{
    Rect2 result;

    ASSERT(min_x <= max_x);
    ASSERT(min_y <= max_y);

    result.min = Vec2_Create(min_x, min_y);
    result.max = Vec2_Create(max_x, max_y);
    return result;
}

Rect2 Rect2_FromMinSize (Vec2 min, Vec2 size)
{
    ASSERT(size.x >= 0.0f);
    ASSERT(size.y >= 0.0f);

    return Rect2_Create(min.x, min.y, min.x + size.x, min.y + size.y);
}

Vec2 Rect2_GetSize (Rect2 rect)
{
    return Vec2_Subtract(rect.max, rect.min);
}

b32 Rect2_ContainsPoint (Rect2 rect, Vec2 point)
{
    return (point.x >= rect.min.x) &&
           (point.y >= rect.min.y) &&
           (point.x < rect.max.x) &&
           (point.y < rect.max.y);
}

b32 Rect2_Intersects (Rect2 a, Rect2 b)
{
    if (a.max.x <= b.min.x) return false;
    if (a.max.y <= b.min.y) return false;
    if (b.max.x <= a.min.x) return false;
    if (b.max.y <= a.min.y) return false;

    return true;
}

RangeUsize RangeUsize_Create (usize min, usize max)
{
    RangeUsize result;

    ASSERT(min <= max);

    result.min = min;
    result.max = max;
    return result;
}

usize RangeUsize_Count (RangeUsize range)
{
    ASSERT(range.min <= range.max);

    return range.max - range.min;
}

b32 RangeUsize_Contains (RangeUsize range, usize value)
{
    return (value >= range.min) && (value < range.max);
}
