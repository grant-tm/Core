#ifndef CORE_BITS_H
#define CORE_BITS_H

#include "core_handle.h"

#define BIT_U32(index) ((u32) 1u << (index))
#define BIT_U64(index) ((u64) 1ull << (index))

b32 Bits_HasAnyU32 (u32 value, u32 flags);
b32 Bits_HasAllU32 (u32 value, u32 flags);
u32 Bits_SetU32 (u32 value, u32 flags);
u32 Bits_ClearU32 (u32 value, u32 flags);
u32 Bits_ToggleU32 (u32 value, u32 flags);
u32 Bits_AssignU32 (u32 value, u32 flags, b32 enabled);

b32 Bits_HasAnyU64 (u64 value, u64 flags);
b32 Bits_HasAllU64 (u64 value, u64 flags);
u64 Bits_SetU64 (u64 value, u64 flags);
u64 Bits_ClearU64 (u64 value, u64 flags);
u64 Bits_ToggleU64 (u64 value, u64 flags);
u64 Bits_AssignU64 (u64 value, u64 flags, b32 enabled);

#endif // CORE_BITS_H
