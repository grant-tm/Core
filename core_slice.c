#include "core_slice.h"

Slice Slice_Create (void *data, usize element_size, usize count)
{
    Slice result;

    ASSERT(element_size > 0);

    if (count > 0)
    {
        ASSERT(data != NULL);
    }

    result.data = data;
    result.element_size = element_size;
    result.count = count;
    return result;
}

b32 Slice_IsEmpty (Slice slice)
{
    return slice.count == 0;
}

usize Slice_GetSize (Slice slice)
{
    return slice.element_size * slice.count;
}

void *Slice_At (Slice slice, usize index)
{
    byte *data;

    ASSERT(index < slice.count);

    data = (byte *) slice.data;
    return data + (index * slice.element_size);
}

Slice Slice_Subslice (Slice slice, usize start_index, usize count)
{
    byte *data;

    ASSERT(start_index <= slice.count);
    ASSERT(count <= (slice.count - start_index));

    data = (byte *) slice.data;
    return Slice_Create(data + (start_index * slice.element_size), slice.element_size, count);
}

Slice Slice_Prefix (Slice slice, usize count)
{
    ASSERT(count <= slice.count);

    return Slice_Subslice(slice, 0, count);
}

Slice Slice_Suffix (Slice slice, usize count)
{
    ASSERT(count <= slice.count);

    return Slice_Subslice(slice, slice.count - count, count);
}

ByteSlice ByteSlice_Create (byte *data, usize count)
{
    ByteSlice result;

    if (count > 0)
    {
        ASSERT(data != NULL);
    }

    result.data = data;
    result.count = count;
    return result;
}

ByteSlice ByteSlice_FromMemory (void *data, usize size)
{
    return ByteSlice_Create((byte *) data, size);
}

ByteSlice ByteSlice_Subslice (ByteSlice slice, usize start_index, usize count)
{
    ASSERT(start_index <= slice.count);
    ASSERT(count <= (slice.count - start_index));

    return ByteSlice_Create(slice.data + start_index, count);
}

U32Slice U32Slice_Create (u32 *data, usize count)
{
    U32Slice result;

    if (count > 0)
    {
        ASSERT(data != NULL);
    }

    result.data = data;
    result.count = count;
    return result;
}

U32Slice U32Slice_Subslice (U32Slice slice, usize start_index, usize count)
{
    ASSERT(start_index <= slice.count);
    ASSERT(count <= (slice.count - start_index));

    return U32Slice_Create(slice.data + start_index, count);
}

F32Slice F32Slice_Create (f32 *data, usize count)
{
    F32Slice result;

    if (count > 0)
    {
        ASSERT(data != NULL);
    }

    result.data = data;
    result.count = count;
    return result;
}

F32Slice F32Slice_Subslice (F32Slice slice, usize start_index, usize count)
{
    ASSERT(start_index <= slice.count);
    ASSERT(count <= (slice.count - start_index));

    return F32Slice_Create(slice.data + start_index, count);
}
