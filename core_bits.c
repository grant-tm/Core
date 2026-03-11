#include "core_bits.h"

b32 Bits_HasAnyU32 (u32 value, u32 flags)
{
    return (value & flags) != 0;
}

b32 Bits_HasAllU32 (u32 value, u32 flags)
{
    return (value & flags) == flags;
}

u32 Bits_SetU32 (u32 value, u32 flags)
{
    return value | flags;
}

u32 Bits_ClearU32 (u32 value, u32 flags)
{
    return value & ~flags;
}

u32 Bits_ToggleU32 (u32 value, u32 flags)
{
    return value ^ flags;
}

u32 Bits_AssignU32 (u32 value, u32 flags, b32 enabled)
{
    if (enabled)
    {
        return Bits_SetU32(value, flags);
    }

    return Bits_ClearU32(value, flags);
}

b32 Bits_HasAnyU64 (u64 value, u64 flags)
{
    return (value & flags) != 0;
}

b32 Bits_HasAllU64 (u64 value, u64 flags)
{
    return (value & flags) == flags;
}

u64 Bits_SetU64 (u64 value, u64 flags)
{
    return value | flags;
}

u64 Bits_ClearU64 (u64 value, u64 flags)
{
    return value & ~flags;
}

u64 Bits_ToggleU64 (u64 value, u64 flags)
{
    return value ^ flags;
}

u64 Bits_AssignU64 (u64 value, u64 flags, b32 enabled)
{
    if (enabled)
    {
        return Bits_SetU64(value, flags);
    }

    return Bits_ClearU64(value, flags);
}
