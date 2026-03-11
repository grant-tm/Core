#ifndef CORE_SLICE_H
#define CORE_SLICE_H

#include "core_math.h"

#define Slice_CreateTyped(data, count) Slice_Create((void *) (data), sizeof(*(data)), (count))
#define Slice_CreateConstTyped(data, count) Slice_Create((void *) (data), sizeof(*(data)), (count))

typedef struct Slice
{
    void *data;
    usize element_size;
    usize count;
} Slice;

typedef struct ByteSlice
{
    byte *data;
    usize count;
} ByteSlice;

typedef struct U32Slice
{
    u32 *data;
    usize count;
} U32Slice;

typedef struct F32Slice
{
    f32 *data;
    usize count;
} F32Slice;

Slice Slice_Create (void *data, usize element_size, usize count);
b32 Slice_IsEmpty (Slice slice);
usize Slice_GetSize (Slice slice);
void *Slice_At (Slice slice, usize index);
Slice Slice_Subslice (Slice slice, usize start_index, usize count);
Slice Slice_Prefix (Slice slice, usize count);
Slice Slice_Suffix (Slice slice, usize count);

ByteSlice ByteSlice_Create (byte *data, usize count);
ByteSlice ByteSlice_FromMemory (void *data, usize size);
ByteSlice ByteSlice_Subslice (ByteSlice slice, usize start_index, usize count);

U32Slice U32Slice_Create (u32 *data, usize count);
U32Slice U32Slice_Subslice (U32Slice slice, usize start_index, usize count);

F32Slice F32Slice_Create (f32 *data, usize count);
F32Slice F32Slice_Subslice (F32Slice slice, usize start_index, usize count);

#endif // CORE_SLICE_H
