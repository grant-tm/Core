#ifndef CORE_RANDOM_H
#define CORE_RANDOM_H

#include "core_hash.h"

typedef struct RandomSeries
{
    u64 state;
} RandomSeries;

RandomSeries RandomSeries_Create (u64 seed);
void RandomSeries_Seed (RandomSeries *series, u64 seed);

u32 Random_U32 (RandomSeries *series);
u64 Random_U64 (RandomSeries *series);
f32 Random_F32 (RandomSeries *series);
f64 Random_F64 (RandomSeries *series);

u32 Random_U32Range (RandomSeries *series, u32 min, u32 max);
u64 Random_U64Range (RandomSeries *series, u64 min, u64 max);
i32 Random_I32Range (RandomSeries *series, i32 min, i32 max);
f32 Random_F32Range (RandomSeries *series, f32 min, f32 max);
f64 Random_F64Range (RandomSeries *series, f64 min, f64 max);

b32 Random_Chance (RandomSeries *series, f32 probability);

#endif // CORE_RANDOM_H
