#include "core_random.h"

static u64 Random_NextState (u64 state)
{
    state ^= state >> 12;
    state ^= state << 25;
    state ^= state >> 27;

    return state;
}

static u64 Random_Scramble (u64 state)
{
    return state * 2685821657736338717ull;
}

RandomSeries RandomSeries_Create (u64 seed)
{
    RandomSeries result;

    RandomSeries_Seed(&result, seed);
    return result;
}

void RandomSeries_Seed (RandomSeries *series, u64 seed)
{
    ASSERT(series != NULL);

    series->state = (seed != 0) ? seed : 0xA5A5A5A5A5A5A5A5ull;
    series->state = Random_NextState(series->state);
}

u32 Random_U32 (RandomSeries *series)
{
    ASSERT(series != NULL);

    series->state = Random_NextState(series->state);
    return (u32) (Random_Scramble(series->state) >> 32);
}

u64 Random_U64 (RandomSeries *series)
{
    u64 high;
    u64 low;

    high = (u64) Random_U32(series);
    low = (u64) Random_U32(series);
    return (high << 32) | low;
}

f32 Random_F32 (RandomSeries *series)
{
    return (f32) Random_U32(series) / (f32) 4294967295.0f;
}

f64 Random_F64 (RandomSeries *series)
{
    return (f64) Random_U64(series) / (f64) 18446744073709551615.0;
}

u32 Random_U32Range (RandomSeries *series, u32 min, u32 max)
{
    u32 range;

    ASSERT(min <= max);

    range = max - min;
    if (range == 0)
    {
        return min;
    }

    if ((min == 0) && (max == 0xFFFFFFFFu))
    {
        return Random_U32(series);
    }

    return min + (Random_U32(series) % (range + 1));
}

u64 Random_U64Range (RandomSeries *series, u64 min, u64 max)
{
    u64 range;

    ASSERT(min <= max);

    range = max - min;
    if (range == 0)
    {
        return min;
    }

    if ((min == 0) && (max == 0xFFFFFFFFFFFFFFFFull))
    {
        return Random_U64(series);
    }

    return min + (Random_U64(series) % (range + 1));
}

i32 Random_I32Range (RandomSeries *series, i32 min, i32 max)
{
    u32 offset;

    ASSERT(min <= max);

    offset = Random_U32Range(series, 0, (u32) (max - min));
    return min + (i32) offset;
}

f32 Random_F32Range (RandomSeries *series, f32 min, f32 max)
{
    ASSERT(min <= max);

    return min + ((max - min) * Random_F32(series));
}

f64 Random_F64Range (RandomSeries *series, f64 min, f64 max)
{
    ASSERT(min <= max);

    return min + ((max - min) * Random_F64(series));
}

b32 Random_Chance (RandomSeries *series, f32 probability)
{
    ASSERT((probability >= 0.0f) && (probability <= 1.0f));

    if (probability <= 0.0f)
    {
        return false;
    }

    if (probability >= 1.0f)
    {
        return true;
    }

    return Random_F32(series) < probability;
}
