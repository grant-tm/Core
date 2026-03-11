#include <stdlib.h>
#include <string.h>

#include "core_memory.h"

static void *Memory_DefaultAllocate (usize size, void *context)
{
    (void) context;
    return malloc(size);
}

static void *Memory_DefaultReallocate (void *memory, usize size, void *context)
{
    (void) context;
    return realloc(memory, size);
}

static void Memory_DefaultFree (void *memory, void *context)
{
    (void) context;
    free(memory);
}

static MemoryAllocator core_memory_allocator =
{
    Memory_DefaultAllocate,
    Memory_DefaultReallocate,
    Memory_DefaultFree,
    NULL,
};

void *Memory_Set (void *memory, i32 value, usize size)
{
    return memset(memory, value, size);
}

void Memory_Zero (void *memory, usize size)
{
    Memory_Set(memory, 0, size);
}

void *Memory_Copy (void *destination, const void *source, usize size)
{
    return memcpy(destination, source, size);
}

void *Memory_Move (void *destination, const void *source, usize size)
{
    return memmove(destination, source, size);
}

i32 Memory_Compare (const void *left, const void *right, usize size)
{
    return memcmp(left, right, size);
}

void Memory_SetAllocator (MemoryAllocator allocator)
{
    ASSERT(allocator.allocate != NULL);
    ASSERT(allocator.reallocate != NULL);
    ASSERT(allocator.free != NULL);

    core_memory_allocator = allocator;
}

MemoryAllocator Memory_GetAllocator (void)
{
    return core_memory_allocator;
}

void *Memory_Allocate (usize size)
{
    return core_memory_allocator.allocate(size, core_memory_allocator.context);
}

void *Memory_Reallocate (void *memory, usize size)
{
    return core_memory_allocator.reallocate(memory, size, core_memory_allocator.context);
}

void Memory_Free (void *memory)
{
    core_memory_allocator.free(memory, core_memory_allocator.context);
}

b32 Memory_IsPowerOfTwo (usize value)
{
    return (value != 0) && ((value & (value - 1)) == 0);
}

usize Memory_GetAlignmentOffset (const void *memory, usize alignment)
{
    usize address;
    usize remainder;

    ASSERT(memory != NULL);
    ASSERT(Memory_IsPowerOfTwo(alignment));

    address = (usize) memory;
    remainder = address & (alignment - 1);

    if (remainder == 0)
    {
        return 0;
    }

    return alignment - remainder;
}

usize Memory_AlignForward (usize value, usize alignment)
{
    ASSERT(Memory_IsPowerOfTwo(alignment));

    return (value + (alignment - 1)) & ~(alignment - 1);
}

void MemoryArena_Init (MemoryArena *arena, void *memory, usize capacity)
{
    ASSERT(arena != NULL);

    arena->memory = (byte *) memory;
    arena->capacity = capacity;
    arena->position = 0;
}

MemoryArena MemoryArena_Create (void *memory, usize capacity)
{
    MemoryArena arena;

    MemoryArena_Init(&arena, memory, capacity);
    return arena;
}

void MemoryArena_Reset (MemoryArena *arena)
{
    ASSERT(arena != NULL);

    arena->position = 0;
}

void *MemoryArena_Push (MemoryArena *arena, usize size, usize alignment)
{
    byte *result;
    usize base_address;
    usize aligned_position;
    usize next_position;

    ASSERT(arena != NULL);
    ASSERT(arena->memory != NULL);
    ASSERT(Memory_IsPowerOfTwo(alignment));

    base_address = (usize) arena->memory;
    aligned_position = Memory_AlignForward(base_address + arena->position, alignment) - base_address;
    next_position = aligned_position + size;

    if (next_position > arena->capacity)
    {
        return NULL;
    }

    result = arena->memory + aligned_position;
    arena->position = next_position;
    return result;
}

void *MemoryArena_PushZero (MemoryArena *arena, usize size, usize alignment)
{
    void *result;

    result = MemoryArena_Push(arena, size, alignment);

    if (result != NULL)
    {
        Memory_Zero(result, size);
    }

    return result;
}

usize MemoryArena_GetUsed (const MemoryArena *arena)
{
    ASSERT(arena != NULL);

    return arena->position;
}

usize MemoryArena_GetRemaining (const MemoryArena *arena)
{
    ASSERT(arena != NULL);
    ASSERT(arena->position <= arena->capacity);

    return arena->capacity - arena->position;
}
