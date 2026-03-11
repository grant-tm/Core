#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

#include "core_assert.h"

#define MEMORY_KILOBYTES(value) ((usize) (value) * 1024u)
#define MEMORY_MEGABYTES(value) (MEMORY_KILOBYTES(value) * 1024u)
#define MEMORY_GIGABYTES(value) (MEMORY_MEGABYTES(value) * 1024u)

#define MEMORY_DEFAULT_ALIGNMENT ((usize) sizeof(void *))
#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

#define Memory_ZeroStruct(value) Memory_Zero((value), sizeof(*(value)))
#define Memory_ZeroArray(values, count) Memory_Zero((values), sizeof(*(values)) * (count))

#define MemoryArena_PushStruct(arena, Type) ((Type *) MemoryArena_Push((arena), sizeof(Type), _Alignof(Type)))
#define MemoryArena_PushArray(arena, Type, count) ((Type *) MemoryArena_Push((arena), sizeof(Type) * (count), _Alignof(Type)))
#define MemoryArena_PushStructZero(arena, Type) ((Type *) MemoryArena_PushZero((arena), sizeof(Type), _Alignof(Type)))
#define MemoryArena_PushArrayZero(arena, Type, count) ((Type *) MemoryArena_PushZero((arena), sizeof(Type) * (count), _Alignof(Type)))

typedef void *MemoryAllocateFunction (usize size, void *context);
typedef void *MemoryReallocateFunction (void *memory, usize size, void *context);
typedef void MemoryFreeFunction (void *memory, void *context);

typedef struct MemoryAllocator
{
    MemoryAllocateFunction *allocate;
    MemoryReallocateFunction *reallocate;
    MemoryFreeFunction *free;
    void *context;
} MemoryAllocator;

typedef struct MemoryArena
{
    byte *memory;
    usize capacity;
    usize position;
} MemoryArena;

void *Memory_Set (void *memory, i32 value, usize size);
void Memory_Zero (void *memory, usize size);
void *Memory_Copy (void *destination, const void *source, usize size);
void *Memory_Move (void *destination, const void *source, usize size);
i32 Memory_Compare (const void *left, const void *right, usize size);

void Memory_SetAllocator (MemoryAllocator allocator);
MemoryAllocator Memory_GetAllocator (void);
void *Memory_Allocate (usize size);
void *Memory_Reallocate (void *memory, usize size);
void Memory_Free (void *memory);

usize Memory_GetAlignmentOffset (const void *memory, usize alignment);
usize Memory_AlignForward (usize value, usize alignment);
b32 Memory_IsPowerOfTwo (usize value);

void MemoryArena_Init (MemoryArena *arena, void *memory, usize capacity);
MemoryArena MemoryArena_Create (void *memory, usize capacity);
void MemoryArena_Reset (MemoryArena *arena);
void *MemoryArena_Push (MemoryArena *arena, usize size, usize alignment);
void *MemoryArena_PushZero (MemoryArena *arena, usize size, usize alignment);
usize MemoryArena_GetUsed (const MemoryArena *arena);
usize MemoryArena_GetRemaining (const MemoryArena *arena);

#endif // CORE_MEMORY_H
