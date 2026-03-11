#include "core_hash.h"

static const Hash32 HASH32_OFFSET_BASIS = 2166136261u;
static const Hash32 HASH32_PRIME = 16777619u;

static const Hash64 HASH64_OFFSET_BASIS = 14695981039346656037ull;
static const Hash64 HASH64_PRIME = 1099511628211ull;

Hash32 Hash32_Bytes (const void *data, usize size)
{
    return Hash32_BytesWithSeed(data, size, HASH32_OFFSET_BASIS);
}

Hash32 Hash32_BytesWithSeed (const void *data, usize size, Hash32 seed)
{
    const byte *bytes;
    Hash32 hash;
    usize index;

    if (size > 0)
    {
        ASSERT(data != NULL);
    }

    bytes = (const byte *) data;
    hash = seed;

    for (index = 0; index < size; index += 1)
    {
        hash ^= bytes[index];
        hash *= HASH32_PRIME;
    }

    return hash;
}

Hash32 Hash32_String (String string)
{
    return Hash32_Bytes(string.data, string.count);
}

Hash64 Hash64_Bytes (const void *data, usize size)
{
    return Hash64_BytesWithSeed(data, size, HASH64_OFFSET_BASIS);
}

Hash64 Hash64_BytesWithSeed (const void *data, usize size, Hash64 seed)
{
    const byte *bytes;
    Hash64 hash;
    usize index;

    if (size > 0)
    {
        ASSERT(data != NULL);
    }

    bytes = (const byte *) data;
    hash = seed;

    for (index = 0; index < size; index += 1)
    {
        hash ^= bytes[index];
        hash *= HASH64_PRIME;
    }

    return hash;
}

Hash64 Hash64_String (String string)
{
    return Hash64_Bytes(string.data, string.count);
}
