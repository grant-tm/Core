#include "core_spsc_ring.h"

static b32 SPSCRing_IsValidDesc (const SPSCRingDesc *desc)
{
    ASSERT(desc != NULL);

    if (desc->storage == NULL) return false;
    if (desc->capacity == 0) return false;
    if (desc->element_size == 0) return false;
    if (desc->element_alignment == 0) return false;
    if (!Memory_IsPowerOfTwo(desc->element_alignment)) return false;
    if ((desc->element_size % desc->element_alignment) != 0) return false;
    if (Memory_GetAlignmentOffset(desc->storage, desc->element_alignment) != 0) return false;

    return true;
}

b32 SPSCRing_Initialize (SPSCRing *ring, const SPSCRingDesc *desc)
{
    ASSERT(ring != NULL);
    ASSERT(desc != NULL);

    Memory_ZeroStruct(ring);

    if (!SPSCRing_IsValidDesc(desc))
    {
        return false;
    }

    ring->storage = (byte *) desc->storage;
    ring->capacity = desc->capacity;
    ring->element_size = desc->element_size;
    ring->element_alignment = desc->element_alignment;

    AtomicU64_Init(&ring->read_position, 0);
    AtomicU64_Init(&ring->write_position, 0);
    return true;
}

void SPSCRing_Reset (SPSCRing *ring)
{
    ASSERT(ring != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    AtomicU64_Store(&ring->read_position, 0, ATOMIC_MEMORY_ORDER_RELAXED);
    AtomicU64_Store(&ring->write_position, 0, ATOMIC_MEMORY_ORDER_RELAXED);
}

void SPSCRing_Shutdown (SPSCRing *ring)
{
    ASSERT(ring != NULL);

    Memory_ZeroStruct(ring);
}

b32 SPSCRing_IsValid (const SPSCRing *ring)
{
    if (ring == NULL) return false;
    if (ring->storage == NULL) return false;
    if (ring->capacity == 0) return false;
    if (ring->element_size == 0) return false;
    if (ring->element_alignment == 0) return false;
    if (!Memory_IsPowerOfTwo(ring->element_alignment)) return false;
    if ((ring->element_size % ring->element_alignment) != 0) return false;
    if (Memory_GetAlignmentOffset(ring->storage, ring->element_alignment) != 0) return false;

    return true;
}

u32 SPSCRing_GetCount (const SPSCRing *ring)
{
    u64 read_position;
    u64 write_position;
    u64 count;

    ASSERT(ring != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    read_position = AtomicU64_Load(&ring->read_position, ATOMIC_MEMORY_ORDER_ACQUIRE);
    write_position = AtomicU64_Load(&ring->write_position, ATOMIC_MEMORY_ORDER_ACQUIRE);
    count = write_position - read_position;
    ASSERT(count <= ring->capacity);

    return (u32) count;
}

u32 SPSCRing_GetCapacity (const SPSCRing *ring)
{
    ASSERT(ring != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    return ring->capacity;
}

b32 SPSCRing_IsEmpty (const SPSCRing *ring)
{
    u64 read_position;
    u64 write_position;

    ASSERT(ring != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    read_position = AtomicU64_Load(&ring->read_position, ATOMIC_MEMORY_ORDER_ACQUIRE);
    write_position = AtomicU64_Load(&ring->write_position, ATOMIC_MEMORY_ORDER_ACQUIRE);
    return read_position == write_position;
}

b32 SPSCRing_IsFull (const SPSCRing *ring)
{
    u64 read_position;
    u64 write_position;

    ASSERT(ring != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    read_position = AtomicU64_Load(&ring->read_position, ATOMIC_MEMORY_ORDER_ACQUIRE);
    write_position = AtomicU64_Load(&ring->write_position, ATOMIC_MEMORY_ORDER_ACQUIRE);

    return (write_position - read_position) == ring->capacity;
}

b32 SPSCRing_TryPush (SPSCRing *ring, const void *element_data)
{
    u64 read_position;
    u64 write_position;
    u64 count;
    u64 write_index;
    byte *destination;

    ASSERT(ring != NULL);
    ASSERT(element_data != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    write_position = AtomicU64_Load(&ring->write_position, ATOMIC_MEMORY_ORDER_RELAXED);
    read_position = AtomicU64_Load(&ring->read_position, ATOMIC_MEMORY_ORDER_ACQUIRE);

    count = write_position - read_position;
    ASSERT(count <= ring->capacity);

    if (count == ring->capacity)
    {
        return false;
    }

    write_index = write_position % ring->capacity;
    destination = ring->storage + ((usize) write_index * ring->element_size);
    Memory_Copy(destination, element_data, ring->element_size);

    AtomicU64_Store(&ring->write_position, write_position + 1, ATOMIC_MEMORY_ORDER_RELEASE);
    return true;
}

b32 SPSCRing_TryPop (SPSCRing *ring, void *element_data)
{
    u64 read_position;
    u64 write_position;
    u64 read_index;
    byte *source;

    ASSERT(ring != NULL);
    ASSERT(element_data != NULL);
    ASSERT(SPSCRing_IsValid(ring));

    read_position = AtomicU64_Load(&ring->read_position, ATOMIC_MEMORY_ORDER_RELAXED);
    write_position = AtomicU64_Load(&ring->write_position, ATOMIC_MEMORY_ORDER_ACQUIRE);

    if (read_position == write_position)
    {
        return false;
    }

    read_index = read_position % ring->capacity;
    source = ring->storage + ((usize) read_index * ring->element_size);
    Memory_Copy(element_data, source, ring->element_size);

    AtomicU64_Store(&ring->read_position, read_position + 1, ATOMIC_MEMORY_ORDER_RELEASE);
    return true;
}
