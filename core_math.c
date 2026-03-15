#include <math.h>

#include "core_math.h"

static f32 F32_ApproxEqualInternal (f32 a, f32 b, f32 epsilon)
{
    f32 difference;
    f32 scale;

    ASSERT(epsilon >= 0.0f);

    difference = F32_Abs(a - b);
    scale = F32_Max(1.0f, F32_Max(F32_Abs(a), F32_Abs(b)));
    return difference <= (epsilon * scale);
}

static f64 F64_ApproxEqualInternal (f64 a, f64 b, f64 epsilon)
{
    f64 difference;
    f64 scale;

    ASSERT(epsilon >= 0.0);

    difference = F64_Abs(a - b);
    scale = F64_Max(1.0, F64_Max(F64_Abs(a), F64_Abs(b)));
    return difference <= (epsilon * scale);
}

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

f32 F32_Sign (f32 value)
{
    if (value > 0.0f) return 1.0f;
    if (value < 0.0f) return -1.0f;

    return 0.0f;
}

f32 F32_Sqrt (f32 value)
{
    ASSERT(value >= 0.0f);

    return sqrtf(value);
}

f32 F32_Exp (f32 value)
{
    return expf(value);
}

f32 F32_Log (f32 value)
{
    ASSERT(value > 0.0f);

    return logf(value);
}

f32 F32_Pow (f32 base, f32 exponent)
{
    return powf(base, exponent);
}

f32 F32_Floor (f32 value)
{
    return floorf(value);
}

f32 F32_Ceil (f32 value)
{
    return ceilf(value);
}

f32 F32_Round (f32 value)
{
    return roundf(value);
}

f32 F32_Mod (f32 numerator, f32 denominator)
{
    ASSERT(denominator != 0.0f);

    return fmodf(numerator, denominator);
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

f32 F32_Tanh (f32 value)
{
    return tanhf(value);
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

b32 F32_IsNan (f32 value)
{
    return isnan(value);
}

b32 F32_IsFinite (f32 value)
{
    return isfinite(value);
}

b32 F32_ApproxEqual (f32 a, f32 b, f32 epsilon)
{
    return F32_ApproxEqualInternal(a, b, epsilon);
}

f64 F64_Abs (f64 value)
{
    return (value < 0.0) ? -value : value;
}

f64 F64_Min (f64 a, f64 b)
{
    return (a < b) ? a : b;
}

f64 F64_Max (f64 a, f64 b)
{
    return (a > b) ? a : b;
}

f64 F64_Clamp (f64 value, f64 min, f64 max)
{
    ASSERT(min <= max);

    return CLAMP(value, min, max);
}

f64 F64_Lerp (f64 a, f64 b, f64 t)
{
    return a + ((b - a) * t);
}

f64 F64_Sign (f64 value)
{
    if (value > 0.0) return 1.0;
    if (value < 0.0) return -1.0;

    return 0.0;
}

f64 F64_Sqrt (f64 value)
{
    ASSERT(value >= 0.0);

    return sqrt(value);
}

f64 F64_Exp (f64 value)
{
    return exp(value);
}

f64 F64_Log (f64 value)
{
    ASSERT(value > 0.0);

    return log(value);
}

f64 F64_Pow (f64 base, f64 exponent)
{
    return pow(base, exponent);
}

f64 F64_Floor (f64 value)
{
    return floor(value);
}

f64 F64_Ceil (f64 value)
{
    return ceil(value);
}

f64 F64_Round (f64 value)
{
    return round(value);
}

f64 F64_Mod (f64 numerator, f64 denominator)
{
    ASSERT(denominator != 0.0);

    return fmod(numerator, denominator);
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

f64 F64_Tanh (f64 value)
{
    return tanh(value);
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

b32 F64_IsNan (f64 value)
{
    return isnan(value);
}

b32 F64_IsFinite (f64 value)
{
    return isfinite(value);
}

b32 F64_ApproxEqual (f64 a, f64 b, f64 epsilon)
{
    return F64_ApproxEqualInternal(a, b, epsilon);
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

Vec2 Vec2_HadamardMultiply (Vec2 a, Vec2 b)
{
    return Vec2_Create(a.x * b.x, a.y * b.y);
}

f32 Vec2_Dot (Vec2 a, Vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

f32 Vec2_LengthSquared (Vec2 value)
{
    return Vec2_Dot(value, value);
}

f32 Vec2_Length (Vec2 value)
{
    return F32_Sqrt(Vec2_LengthSquared(value));
}

Vec2 Vec2_Normalize (Vec2 value)
{
    f32 length;

    length = Vec2_Length(value);
    ASSERT(length > 0.0f);

    return Vec2_Scale(value, 1.0f / length);
}

f32 Vec2_DistanceSquared (Vec2 a, Vec2 b)
{
    return Vec2_LengthSquared(Vec2_Subtract(a, b));
}

f32 Vec2_Distance (Vec2 a, Vec2 b)
{
    return F32_Sqrt(Vec2_DistanceSquared(a, b));
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

Vec3 Vec3_HadamardMultiply (Vec3 a, Vec3 b)
{
    return Vec3_Create(a.x * b.x, a.y * b.y, a.z * b.z);
}

f32 Vec3_Dot (Vec3 a, Vec3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 Vec3_Cross (Vec3 a, Vec3 b)
{
    return Vec3_Create(
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    );
}

f32 Vec3_LengthSquared (Vec3 value)
{
    return Vec3_Dot(value, value);
}

f32 Vec3_Length (Vec3 value)
{
    return F32_Sqrt(Vec3_LengthSquared(value));
}

Vec3 Vec3_Normalize (Vec3 value)
{
    f32 length;

    length = Vec3_Length(value);
    ASSERT(length > 0.0f);

    return Vec3_Scale(value, 1.0f / length);
}

f32 Vec3_DistanceSquared (Vec3 a, Vec3 b)
{
    return Vec3_LengthSquared(Vec3_Subtract(a, b));
}

f32 Vec3_Distance (Vec3 a, Vec3 b)
{
    return F32_Sqrt(Vec3_DistanceSquared(a, b));
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

Vec4 Vec4_Add (Vec4 a, Vec4 b)
{
    return Vec4_Create(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

Vec4 Vec4_Subtract (Vec4 a, Vec4 b)
{
    return Vec4_Create(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Vec4 Vec4_Scale (Vec4 value, f32 scalar)
{
    return Vec4_Create(value.x * scalar, value.y * scalar, value.z * scalar, value.w * scalar);
}

Vec4 Vec4_HadamardMultiply (Vec4 a, Vec4 b)
{
    return Vec4_Create(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

f32 Vec4_Dot (Vec4 a, Vec4 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

f32 Vec4_LengthSquared (Vec4 value)
{
    return Vec4_Dot(value, value);
}

f32 Vec4_Length (Vec4 value)
{
    return F32_Sqrt(Vec4_LengthSquared(value));
}

Vec4 Vec4_Normalize (Vec4 value)
{
    f32 length;

    length = Vec4_Length(value);
    ASSERT(length > 0.0f);

    return Vec4_Scale(value, 1.0f / length);
}

Mat2 Mat2_Create (f32 e00, f32 e01, f32 e10, f32 e11)
{
    Mat2 result;

    result.elements[0][0] = e00;
    result.elements[0][1] = e01;
    result.elements[1][0] = e10;
    result.elements[1][1] = e11;
    return result;
}

Mat2 Mat2_CreateIdentity (void)
{
    return Mat2_Create(
        1.0f, 0.0f,
        0.0f, 1.0f
    );
}

Mat2 Mat2_Transpose (Mat2 matrix)
{
    return Mat2_Create(
        matrix.elements[0][0], matrix.elements[1][0],
        matrix.elements[0][1], matrix.elements[1][1]
    );
}

Mat2 Mat2_Multiply (Mat2 left, Mat2 right)
{
    Mat2 result;
    usize row;
    usize column;

    for (row = 0; row < 2; row += 1)
    {
        for (column = 0; column < 2; column += 1)
        {
            result.elements[row][column] =
                (left.elements[row][0] * right.elements[0][column]) +
                (left.elements[row][1] * right.elements[1][column]);
        }
    }

    return result;
}

Vec2 Mat2_MultiplyVec2 (Mat2 matrix, Vec2 vector)
{
    return Vec2_Create(
        (matrix.elements[0][0] * vector.x) + (matrix.elements[0][1] * vector.y),
        (matrix.elements[1][0] * vector.x) + (matrix.elements[1][1] * vector.y)
    );
}

Mat3 Mat3_Create (
    f32 e00, f32 e01, f32 e02,
    f32 e10, f32 e11, f32 e12,
    f32 e20, f32 e21, f32 e22
)
{
    Mat3 result;

    result.elements[0][0] = e00;
    result.elements[0][1] = e01;
    result.elements[0][2] = e02;
    result.elements[1][0] = e10;
    result.elements[1][1] = e11;
    result.elements[1][2] = e12;
    result.elements[2][0] = e20;
    result.elements[2][1] = e21;
    result.elements[2][2] = e22;
    return result;
}

Mat3 Mat3_CreateIdentity (void)
{
    return Mat3_Create(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
}

Mat3 Mat3_Transpose (Mat3 matrix)
{
    return Mat3_Create(
        matrix.elements[0][0], matrix.elements[1][0], matrix.elements[2][0],
        matrix.elements[0][1], matrix.elements[1][1], matrix.elements[2][1],
        matrix.elements[0][2], matrix.elements[1][2], matrix.elements[2][2]
    );
}

Mat3 Mat3_Multiply (Mat3 left, Mat3 right)
{
    Mat3 result;
    usize row;
    usize column;

    for (row = 0; row < 3; row += 1)
    {
        for (column = 0; column < 3; column += 1)
        {
            result.elements[row][column] =
                (left.elements[row][0] * right.elements[0][column]) +
                (left.elements[row][1] * right.elements[1][column]) +
                (left.elements[row][2] * right.elements[2][column]);
        }
    }

    return result;
}

Vec3 Mat3_MultiplyVec3 (Mat3 matrix, Vec3 vector)
{
    return Vec3_Create(
        (matrix.elements[0][0] * vector.x) + (matrix.elements[0][1] * vector.y) + (matrix.elements[0][2] * vector.z),
        (matrix.elements[1][0] * vector.x) + (matrix.elements[1][1] * vector.y) + (matrix.elements[1][2] * vector.z),
        (matrix.elements[2][0] * vector.x) + (matrix.elements[2][1] * vector.y) + (matrix.elements[2][2] * vector.z)
    );
}

Mat4 Mat4_Create (
    f32 e00, f32 e01, f32 e02, f32 e03,
    f32 e10, f32 e11, f32 e12, f32 e13,
    f32 e20, f32 e21, f32 e22, f32 e23,
    f32 e30, f32 e31, f32 e32, f32 e33
)
{
    Mat4 result;

    result.elements[0][0] = e00;
    result.elements[0][1] = e01;
    result.elements[0][2] = e02;
    result.elements[0][3] = e03;
    result.elements[1][0] = e10;
    result.elements[1][1] = e11;
    result.elements[1][2] = e12;
    result.elements[1][3] = e13;
    result.elements[2][0] = e20;
    result.elements[2][1] = e21;
    result.elements[2][2] = e22;
    result.elements[2][3] = e23;
    result.elements[3][0] = e30;
    result.elements[3][1] = e31;
    result.elements[3][2] = e32;
    result.elements[3][3] = e33;
    return result;
}

Mat4 Mat4_CreateIdentity (void)
{
    return Mat4_Create(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Mat4 Mat4_Transpose (Mat4 matrix)
{
    return Mat4_Create(
        matrix.elements[0][0], matrix.elements[1][0], matrix.elements[2][0], matrix.elements[3][0],
        matrix.elements[0][1], matrix.elements[1][1], matrix.elements[2][1], matrix.elements[3][1],
        matrix.elements[0][2], matrix.elements[1][2], matrix.elements[2][2], matrix.elements[3][2],
        matrix.elements[0][3], matrix.elements[1][3], matrix.elements[2][3], matrix.elements[3][3]
    );
}

Mat4 Mat4_Multiply (Mat4 left, Mat4 right)
{
    Mat4 result;
    usize row;
    usize column;

    for (row = 0; row < 4; row += 1)
    {
        for (column = 0; column < 4; column += 1)
        {
            result.elements[row][column] =
                (left.elements[row][0] * right.elements[0][column]) +
                (left.elements[row][1] * right.elements[1][column]) +
                (left.elements[row][2] * right.elements[2][column]) +
                (left.elements[row][3] * right.elements[3][column]);
        }
    }

    return result;
}

Vec4 Mat4_MultiplyVec4 (Mat4 matrix, Vec4 vector)
{
    return Vec4_Create(
        (matrix.elements[0][0] * vector.x) + (matrix.elements[0][1] * vector.y) + (matrix.elements[0][2] * vector.z) + (matrix.elements[0][3] * vector.w),
        (matrix.elements[1][0] * vector.x) + (matrix.elements[1][1] * vector.y) + (matrix.elements[1][2] * vector.z) + (matrix.elements[1][3] * vector.w),
        (matrix.elements[2][0] * vector.x) + (matrix.elements[2][1] * vector.y) + (matrix.elements[2][2] * vector.z) + (matrix.elements[2][3] * vector.w),
        (matrix.elements[3][0] * vector.x) + (matrix.elements[3][1] * vector.y) + (matrix.elements[3][2] * vector.z) + (matrix.elements[3][3] * vector.w)
    );
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

SpanF32 SpanF32_Create (f32 *values, usize count)
{
    SpanF32 result;

    if (count > 0) ASSERT(values != NULL);

    result.values = values;
    result.count = count;
    return result;
}

f32 SpanF32_Sum (SpanF32 span)
{
    f32 result;
    usize index;

    result = 0.0f;

    for (index = 0; index < span.count; index += 1)
    {
        result += span.values[index];
    }

    return result;
}

f32 SpanF32_Mean (SpanF32 span)
{
    ASSERT(span.count > 0);

    return SpanF32_Sum(span) / (f32) span.count;
}

f32 SpanF32_Min (SpanF32 span)
{
    f32 result;
    usize index;

    ASSERT(span.count > 0);

    result = span.values[0];

    for (index = 1; index < span.count; index += 1)
    {
        result = F32_Min(result, span.values[index]);
    }

    return result;
}

f32 SpanF32_Max (SpanF32 span)
{
    f32 result;
    usize index;

    ASSERT(span.count > 0);

    result = span.values[0];

    for (index = 1; index < span.count; index += 1)
    {
        result = F32_Max(result, span.values[index]);
    }

    return result;
}

usize SpanF32_ArgMin (SpanF32 span)
{
    usize result;
    usize index;

    ASSERT(span.count > 0);

    result = 0;

    for (index = 1; index < span.count; index += 1)
    {
        if (span.values[index] < span.values[result])
        {
            result = index;
        }
    }

    return result;
}

usize SpanF32_ArgMax (SpanF32 span)
{
    usize result;
    usize index;

    ASSERT(span.count > 0);

    result = 0;

    for (index = 1; index < span.count; index += 1)
    {
        if (span.values[index] > span.values[result])
        {
            result = index;
        }
    }

    return result;
}

f32 SpanF32_Variance (SpanF32 span)
{
    f32 mean;
    f32 sum;
    usize index;

    ASSERT(span.count > 0);

    mean = SpanF32_Mean(span);
    sum = 0.0f;

    for (index = 0; index < span.count; index += 1)
    {
        f32 difference;

        difference = span.values[index] - mean;
        sum += difference * difference;
    }

    return sum / (f32) span.count;
}

f32 SpanF32_StandardDeviation (SpanF32 span)
{
    return F32_Sqrt(SpanF32_Variance(span));
}

SpanF64 SpanF64_Create (f64 *values, usize count)
{
    SpanF64 result;

    if (count > 0) ASSERT(values != NULL);

    result.values = values;
    result.count = count;
    return result;
}

f64 SpanF64_Sum (SpanF64 span)
{
    f64 result;
    usize index;

    result = 0.0;

    for (index = 0; index < span.count; index += 1)
    {
        result += span.values[index];
    }

    return result;
}

f64 SpanF64_Mean (SpanF64 span)
{
    ASSERT(span.count > 0);

    return SpanF64_Sum(span) / (f64) span.count;
}

f64 SpanF64_Min (SpanF64 span)
{
    f64 result;
    usize index;

    ASSERT(span.count > 0);

    result = span.values[0];

    for (index = 1; index < span.count; index += 1)
    {
        result = F64_Min(result, span.values[index]);
    }

    return result;
}

f64 SpanF64_Max (SpanF64 span)
{
    f64 result;
    usize index;

    ASSERT(span.count > 0);

    result = span.values[0];

    for (index = 1; index < span.count; index += 1)
    {
        result = F64_Max(result, span.values[index]);
    }

    return result;
}

usize SpanF64_ArgMin (SpanF64 span)
{
    usize result;
    usize index;

    ASSERT(span.count > 0);

    result = 0;

    for (index = 1; index < span.count; index += 1)
    {
        if (span.values[index] < span.values[result])
        {
            result = index;
        }
    }

    return result;
}

usize SpanF64_ArgMax (SpanF64 span)
{
    usize result;
    usize index;

    ASSERT(span.count > 0);

    result = 0;

    for (index = 1; index < span.count; index += 1)
    {
        if (span.values[index] > span.values[result])
        {
            result = index;
        }
    }

    return result;
}

f64 SpanF64_Variance (SpanF64 span)
{
    f64 mean;
    f64 sum;
    usize index;

    ASSERT(span.count > 0);

    mean = SpanF64_Mean(span);
    sum = 0.0;

    for (index = 0; index < span.count; index += 1)
    {
        f64 difference;

        difference = span.values[index] - mean;
        sum += difference * difference;
    }

    return sum / (f64) span.count;
}

f64 SpanF64_StandardDeviation (SpanF64 span)
{
    return F64_Sqrt(SpanF64_Variance(span));
}
