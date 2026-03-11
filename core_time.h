#ifndef CORE_TIME_H
#define CORE_TIME_H

#include "core_slice.h"

typedef i64 Nanoseconds;
typedef i64 Microseconds;
typedef i64 Milliseconds;
typedef i64 Seconds;

static const Nanoseconds NANOSECONDS_PER_MICROSECOND = 1000;
static const Nanoseconds NANOSECONDS_PER_MILLISECOND = 1000 * 1000;
static const Nanoseconds NANOSECONDS_PER_SECOND = 1000 * 1000 * 1000;

static const Microseconds MICROSECONDS_PER_MILLISECOND = 1000;
static const Microseconds MICROSECONDS_PER_SECOND = 1000 * 1000;

static const Milliseconds MILLISECONDS_PER_SECOND = 1000;

Nanoseconds Nanoseconds_FromMicroseconds (Microseconds microseconds);
Nanoseconds Nanoseconds_FromMilliseconds (Milliseconds milliseconds);
Nanoseconds Nanoseconds_FromSeconds (Seconds seconds);
Nanoseconds Nanoseconds_FromSecondsF32 (f32 seconds);
Nanoseconds Nanoseconds_FromSecondsF64 (f64 seconds);

Microseconds Microseconds_FromNanoseconds (Nanoseconds nanoseconds);
Microseconds Microseconds_FromMilliseconds (Milliseconds milliseconds);
Microseconds Microseconds_FromSeconds (Seconds seconds);

Milliseconds Milliseconds_FromNanoseconds (Nanoseconds nanoseconds);
Milliseconds Milliseconds_FromMicroseconds (Microseconds microseconds);
Milliseconds Milliseconds_FromSeconds (Seconds seconds);

Seconds Seconds_FromNanoseconds (Nanoseconds nanoseconds);
Seconds Seconds_FromMicroseconds (Microseconds microseconds);
Seconds Seconds_FromMilliseconds (Milliseconds milliseconds);

f32 SecondsF32_FromNanoseconds (Nanoseconds nanoseconds);
f32 SecondsF32_FromMicroseconds (Microseconds microseconds);
f32 SecondsF32_FromMilliseconds (Milliseconds milliseconds);

f64 SecondsF64_FromNanoseconds (Nanoseconds nanoseconds);
f64 SecondsF64_FromMicroseconds (Microseconds microseconds);
f64 SecondsF64_FromMilliseconds (Milliseconds milliseconds);

#endif // CORE_TIME_H
