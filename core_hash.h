#ifndef CORE_HASH_H
#define CORE_HASH_H

#include "core_serialize.h"

typedef u32 Hash32;
typedef u64 Hash64;

Hash32 Hash32_Bytes (const void *data, usize size);
Hash32 Hash32_BytesWithSeed (const void *data, usize size, Hash32 seed);
Hash32 Hash32_String (String string);

Hash64 Hash64_Bytes (const void *data, usize size);
Hash64 Hash64_BytesWithSeed (const void *data, usize size, Hash64 seed);
Hash64 Hash64_String (String string);

#endif // CORE_HASH_H
