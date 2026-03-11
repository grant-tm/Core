#include "core_time.h"

Nanoseconds Nanoseconds_FromMicroseconds (Microseconds microseconds)
{
    return microseconds * NANOSECONDS_PER_MICROSECOND;
}

Nanoseconds Nanoseconds_FromMilliseconds (Milliseconds milliseconds)
{
    return milliseconds * NANOSECONDS_PER_MILLISECOND;
}

Nanoseconds Nanoseconds_FromSeconds (Seconds seconds)
{
    return seconds * NANOSECONDS_PER_SECOND;
}

Nanoseconds Nanoseconds_FromSecondsF32 (f32 seconds)
{
    return (Nanoseconds) (seconds * (f32) NANOSECONDS_PER_SECOND);
}

Nanoseconds Nanoseconds_FromSecondsF64 (f64 seconds)
{
    return (Nanoseconds) (seconds * (f64) NANOSECONDS_PER_SECOND);
}

Microseconds Microseconds_FromNanoseconds (Nanoseconds nanoseconds)
{
    return nanoseconds / NANOSECONDS_PER_MICROSECOND;
}

Microseconds Microseconds_FromMilliseconds (Milliseconds milliseconds)
{
    return milliseconds * MICROSECONDS_PER_MILLISECOND;
}

Microseconds Microseconds_FromSeconds (Seconds seconds)
{
    return seconds * MICROSECONDS_PER_SECOND;
}

Milliseconds Milliseconds_FromNanoseconds (Nanoseconds nanoseconds)
{
    return nanoseconds / NANOSECONDS_PER_MILLISECOND;
}

Milliseconds Milliseconds_FromMicroseconds (Microseconds microseconds)
{
    return microseconds / MICROSECONDS_PER_MILLISECOND;
}

Milliseconds Milliseconds_FromSeconds (Seconds seconds)
{
    return seconds * MILLISECONDS_PER_SECOND;
}

Seconds Seconds_FromNanoseconds (Nanoseconds nanoseconds)
{
    return nanoseconds / NANOSECONDS_PER_SECOND;
}

Seconds Seconds_FromMicroseconds (Microseconds microseconds)
{
    return microseconds / MICROSECONDS_PER_SECOND;
}

Seconds Seconds_FromMilliseconds (Milliseconds milliseconds)
{
    return milliseconds / MILLISECONDS_PER_SECOND;
}

f32 SecondsF32_FromNanoseconds (Nanoseconds nanoseconds)
{
    return (f32) nanoseconds / (f32) NANOSECONDS_PER_SECOND;
}

f32 SecondsF32_FromMicroseconds (Microseconds microseconds)
{
    return (f32) microseconds / (f32) MICROSECONDS_PER_SECOND;
}

f32 SecondsF32_FromMilliseconds (Milliseconds milliseconds)
{
    return (f32) milliseconds / (f32) MILLISECONDS_PER_SECOND;
}

f64 SecondsF64_FromNanoseconds (Nanoseconds nanoseconds)
{
    return (f64) nanoseconds / (f64) NANOSECONDS_PER_SECOND;
}

f64 SecondsF64_FromMicroseconds (Microseconds microseconds)
{
    return (f64) microseconds / (f64) MICROSECONDS_PER_SECOND;
}

f64 SecondsF64_FromMilliseconds (Milliseconds milliseconds)
{
    return (f64) milliseconds / (f64) MILLISECONDS_PER_SECOND;
}
