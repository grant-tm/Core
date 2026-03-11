#include "core_handle.h"

Handle32 Handle32_Create (u32 value)
{
    return value;
}

Handle64 Handle64_Create (u64 value)
{
    return value;
}

b32 Handle32_IsValid (Handle32 handle)
{
    return handle != HANDLE32_INVALID;
}

b32 Handle64_IsValid (Handle64 handle)
{
    return handle != HANDLE64_INVALID;
}

GenerationalHandle32 GenerationalHandle32_Create (u32 index, u32 generation)
{
    GenerationalHandle32 result;

    result.index = index;
    result.generation = generation;
    return result;
}

GenerationalHandle64 GenerationalHandle64_Create (u32 index, u32 generation)
{
    GenerationalHandle64 result;

    result.index = index;
    result.generation = generation;
    return result;
}

b32 GenerationalHandle32_IsValid (GenerationalHandle32 handle)
{
    return (handle.index != 0) && (handle.generation != 0);
}

b32 GenerationalHandle64_IsValid (GenerationalHandle64 handle)
{
    return (handle.index != 0) && (handle.generation != 0);
}

b32 GenerationalHandle32_Equals (GenerationalHandle32 a, GenerationalHandle32 b)
{
    return (a.index == b.index) && (a.generation == b.generation);
}

b32 GenerationalHandle64_Equals (GenerationalHandle64 a, GenerationalHandle64 b)
{
    return (a.index == b.index) && (a.generation == b.generation);
}

Handle64 GenerationalHandle64_Pack (GenerationalHandle64 handle)
{
    return (((u64) handle.generation) << 32) | (u64) handle.index;
}

GenerationalHandle64 GenerationalHandle64_Unpack (Handle64 packed_handle)
{
    GenerationalHandle64 result;

    result.index = (u32) (packed_handle & 0xFFFFFFFFu);
    result.generation = (u32) (packed_handle >> 32);
    return result;
}
