#include "core_atomic.h"

#include "core_assert.h"

#if CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    #include <intrin.h>
#endif

static b32 Atomic_IsValidMemoryOrder (AtomicMemoryOrder order)
{
    return (order >= ATOMIC_MEMORY_ORDER_RELAXED) && (order <= ATOMIC_MEMORY_ORDER_SEQ_CST);
}

static b32 Atomic_IsValidLoadOrder (AtomicMemoryOrder order)
{
    if (!Atomic_IsValidMemoryOrder(order)) return false;
    if (order == ATOMIC_MEMORY_ORDER_RELEASE) return false;
    if (order == ATOMIC_MEMORY_ORDER_ACQ_REL) return false;
    return true;
}

static b32 Atomic_IsValidStoreOrder (AtomicMemoryOrder order)
{
    if (!Atomic_IsValidMemoryOrder(order)) return false;
    if (order == ATOMIC_MEMORY_ORDER_ACQUIRE) return false;
    if (order == ATOMIC_MEMORY_ORDER_CONSUME) return false;
    if (order == ATOMIC_MEMORY_ORDER_ACQ_REL) return false;
    return true;
}

static b32 Atomic_IsValidCompareExchangeFailureOrder (AtomicMemoryOrder order)
{
    if (!Atomic_IsValidMemoryOrder(order)) return false;
    if (order == ATOMIC_MEMORY_ORDER_RELEASE) return false;
    if (order == ATOMIC_MEMORY_ORDER_ACQ_REL) return false;
    return true;
}

static i32 Atomic_MemoryOrderStrength (AtomicMemoryOrder order)
{
    ASSERT(Atomic_IsValidMemoryOrder(order));

    switch (order)
    {
        case ATOMIC_MEMORY_ORDER_RELAXED: return 0;
        case ATOMIC_MEMORY_ORDER_CONSUME: return 1;
        case ATOMIC_MEMORY_ORDER_ACQUIRE: return 2;
        case ATOMIC_MEMORY_ORDER_RELEASE: return 2;
        case ATOMIC_MEMORY_ORDER_ACQ_REL: return 3;
        case ATOMIC_MEMORY_ORDER_SEQ_CST: return 4;
    }

    UNREACHABLE();
    return 0;
}

#if CORE_ATOMIC_BACKEND_STDATOMIC
static memory_order Atomic_ToStdMemoryOrder (AtomicMemoryOrder order)
{
    ASSERT(Atomic_IsValidMemoryOrder(order));

    switch (order)
    {
        case ATOMIC_MEMORY_ORDER_RELAXED: return memory_order_relaxed;
        case ATOMIC_MEMORY_ORDER_CONSUME: return memory_order_consume;
        case ATOMIC_MEMORY_ORDER_ACQUIRE: return memory_order_acquire;
        case ATOMIC_MEMORY_ORDER_RELEASE: return memory_order_release;
        case ATOMIC_MEMORY_ORDER_ACQ_REL: return memory_order_acq_rel;
        case ATOMIC_MEMORY_ORDER_SEQ_CST: return memory_order_seq_cst;
    }

    UNREACHABLE();
    return memory_order_seq_cst;
}
#elif CORE_ATOMIC_BACKEND_GNUC_ATOMICS
static i32 Atomic_ToGnuMemoryOrder (AtomicMemoryOrder order)
{
    ASSERT(Atomic_IsValidMemoryOrder(order));

    switch (order)
    {
        case ATOMIC_MEMORY_ORDER_RELAXED: return __ATOMIC_RELAXED;
        case ATOMIC_MEMORY_ORDER_CONSUME: return __ATOMIC_CONSUME;
        case ATOMIC_MEMORY_ORDER_ACQUIRE: return __ATOMIC_ACQUIRE;
        case ATOMIC_MEMORY_ORDER_RELEASE: return __ATOMIC_RELEASE;
        case ATOMIC_MEMORY_ORDER_ACQ_REL: return __ATOMIC_ACQ_REL;
        case ATOMIC_MEMORY_ORDER_SEQ_CST: return __ATOMIC_SEQ_CST;
    }

    UNREACHABLE();
    return __ATOMIC_SEQ_CST;
}
#endif

void Atomic_ThreadFence (AtomicMemoryOrder order)
{
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_thread_fence(Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    MemoryBarrier();
#else
    __atomic_thread_fence(Atomic_ToGnuMemoryOrder(order));
#endif
}

void Atomic_SignalFence (AtomicMemoryOrder order)
{
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_signal_fence(Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    _ReadWriteBarrier();
#else
    __asm__ __volatile__ ("" ::: "memory");
#endif
}

void AtomicU32_Init (AtomicU32 *atomic, u32 value)
{
    ASSERT(atomic != NULL);

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_init(&atomic->value, value);
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    _InterlockedExchange((volatile long *) &atomic->value, (long) value);
#else
    __atomic_store_n(&atomic->value, value, __ATOMIC_RELAXED);
#endif
}

u32 AtomicU32_Load (const AtomicU32 *atomic, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidLoadOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_load_explicit(&atomic->value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u32) _InterlockedOr((volatile long *) &atomic->value, 0);
#else
    return __atomic_load_n(&atomic->value, Atomic_ToGnuMemoryOrder(order));
#endif
}

void AtomicU32_Store (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidStoreOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_store_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    _InterlockedExchange((volatile long *) &atomic->value, (long) value);
#else
    __atomic_store_n(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

u32 AtomicU32_Exchange (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_exchange_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u32) _InterlockedExchange((volatile long *) &atomic->value, (long) value);
#else
    return __atomic_exchange_n(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

b32 AtomicU32_CompareExchange (
    AtomicU32 *atomic,
    u32 *expected,
    u32 desired,
    AtomicMemoryOrder success_order,
    AtomicMemoryOrder failure_order)
{
    ASSERT(atomic != NULL);
    ASSERT(expected != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(success_order));
    ASSERT(Atomic_IsValidCompareExchangeFailureOrder(failure_order));
    ASSERT(Atomic_MemoryOrderStrength(failure_order) <= Atomic_MemoryOrderStrength(success_order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_compare_exchange_strong_explicit(
        &atomic->value,
        expected,
        desired,
        Atomic_ToStdMemoryOrder(success_order),
        Atomic_ToStdMemoryOrder(failure_order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    long expected_value;
    long result;

    (void) success_order;
    (void) failure_order;

    expected_value = (long) *expected;
    result = _InterlockedCompareExchange((volatile long *) &atomic->value, (long) desired, expected_value);
    if (result == expected_value)
    {
        return true;
    }

    *expected = (u32) result;
    return false;
#else
    return __atomic_compare_exchange_n(
        &atomic->value,
        expected,
        desired,
        false,
        Atomic_ToGnuMemoryOrder(success_order),
        Atomic_ToGnuMemoryOrder(failure_order));
#endif
}

u32 AtomicU32_FetchAdd (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_fetch_add_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u32) _InterlockedExchangeAdd((volatile long *) &atomic->value, (long) value);
#else
    return __atomic_fetch_add(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

u32 AtomicU32_FetchSub (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_fetch_sub_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u32) _InterlockedExchangeAdd((volatile long *) &atomic->value, (long) (0u - value));
#else
    return __atomic_fetch_sub(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

void AtomicU64_Init (AtomicU64 *atomic, u64 value)
{
    ASSERT(atomic != NULL);

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_init(&atomic->value, value);
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    _InterlockedExchange64((volatile long long *) &atomic->value, (long long) value);
#else
    __atomic_store_n(&atomic->value, value, __ATOMIC_RELAXED);
#endif
}

u64 AtomicU64_Load (const AtomicU64 *atomic, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidLoadOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_load_explicit(&atomic->value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u64) _InterlockedOr64((volatile long long *) &atomic->value, 0);
#else
    return __atomic_load_n(&atomic->value, Atomic_ToGnuMemoryOrder(order));
#endif
}

void AtomicU64_Store (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidStoreOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    atomic_store_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    _InterlockedExchange64((volatile long long *) &atomic->value, (long long) value);
#else
    __atomic_store_n(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

u64 AtomicU64_Exchange (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_exchange_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u64) _InterlockedExchange64((volatile long long *) &atomic->value, (long long) value);
#else
    return __atomic_exchange_n(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

b32 AtomicU64_CompareExchange (
    AtomicU64 *atomic,
    u64 *expected,
    u64 desired,
    AtomicMemoryOrder success_order,
    AtomicMemoryOrder failure_order)
{
    ASSERT(atomic != NULL);
    ASSERT(expected != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(success_order));
    ASSERT(Atomic_IsValidCompareExchangeFailureOrder(failure_order));
    ASSERT(Atomic_MemoryOrderStrength(failure_order) <= Atomic_MemoryOrderStrength(success_order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_compare_exchange_strong_explicit(
        &atomic->value,
        expected,
        desired,
        Atomic_ToStdMemoryOrder(success_order),
        Atomic_ToStdMemoryOrder(failure_order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    long long expected_value;
    long long result;

    (void) success_order;
    (void) failure_order;

    expected_value = (long long) *expected;
    result = _InterlockedCompareExchange64((volatile long long *) &atomic->value, (long long) desired, expected_value);
    if (result == expected_value)
    {
        return true;
    }

    *expected = (u64) result;
    return false;
#else
    return __atomic_compare_exchange_n(
        &atomic->value,
        expected,
        desired,
        false,
        Atomic_ToGnuMemoryOrder(success_order),
        Atomic_ToGnuMemoryOrder(failure_order));
#endif
}

u64 AtomicU64_FetchAdd (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_fetch_add_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u64) _InterlockedExchangeAdd64((volatile long long *) &atomic->value, (long long) value);
#else
    return __atomic_fetch_add(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}

u64 AtomicU64_FetchSub (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order)
{
    ASSERT(atomic != NULL);
    ASSERT(Atomic_IsValidMemoryOrder(order));

#if CORE_ATOMIC_BACKEND_STDATOMIC
    return atomic_fetch_sub_explicit(&atomic->value, value, Atomic_ToStdMemoryOrder(order));
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    (void) order;
    return (u64) _InterlockedExchangeAdd64((volatile long long *) &atomic->value, (long long) (0ull - value));
#else
    return __atomic_fetch_sub(&atomic->value, value, Atomic_ToGnuMemoryOrder(order));
#endif
}
