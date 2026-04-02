#ifndef CORE_SPSC_RING_H
#define CORE_SPSC_RING_H

#include "core_atomic.h"
#include "core_memory.h"

typedef struct SPSCRingDesc
{
    void *storage;
    u32 capacity;
    u32 element_size;
    u32 element_alignment;
} SPSCRingDesc;

typedef struct SPSCRing
{
    byte *storage;
    u32 capacity;
    u32 element_size;
    u32 element_alignment;
    AtomicU64 read_position;
    AtomicU64 write_position;
} SPSCRing;

b32 SPSCRing_Initialize (SPSCRing *ring, const SPSCRingDesc *desc);
void SPSCRing_Reset (SPSCRing *ring);
void SPSCRing_Shutdown (SPSCRing *ring);
b32 SPSCRing_IsValid (const SPSCRing *ring);
u32 SPSCRing_GetCount (const SPSCRing *ring);
u32 SPSCRing_GetCapacity (const SPSCRing *ring);
b32 SPSCRing_IsEmpty (const SPSCRing *ring);
b32 SPSCRing_IsFull (const SPSCRing *ring);

b32 SPSCRing_TryPush (SPSCRing *ring, const void *element_data);
b32 SPSCRing_TryPop (SPSCRing *ring, void *element_data);

#endif // CORE_SPSC_RING_H
