#ifndef CORE_HANDLE_H
#define CORE_HANDLE_H

#include "core_time.h"

#define HANDLE32_INVALID ((Handle32) 0)
#define HANDLE64_INVALID ((Handle64) 0)

typedef u32 Handle32;
typedef u64 Handle64;

typedef struct GenerationalHandle32
{
    u32 index;
    u32 generation;
} GenerationalHandle32;

typedef struct GenerationalHandle64
{
    u32 index;
    u32 generation;
} GenerationalHandle64;

Handle32 Handle32_Create (u32 value);
Handle64 Handle64_Create (u64 value);
b32 Handle32_IsValid (Handle32 handle);
b32 Handle64_IsValid (Handle64 handle);

GenerationalHandle32 GenerationalHandle32_Create (u32 index, u32 generation);
GenerationalHandle64 GenerationalHandle64_Create (u32 index, u32 generation);
b32 GenerationalHandle32_IsValid (GenerationalHandle32 handle);
b32 GenerationalHandle64_IsValid (GenerationalHandle64 handle);
b32 GenerationalHandle32_Equals (GenerationalHandle32 a, GenerationalHandle32 b);
b32 GenerationalHandle64_Equals (GenerationalHandle64 a, GenerationalHandle64 b);

Handle64 GenerationalHandle64_Pack (GenerationalHandle64 handle);
GenerationalHandle64 GenerationalHandle64_Unpack (Handle64 packed_handle);

#endif // CORE_HANDLE_H
