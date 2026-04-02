#ifndef CORE_ATOMIC_H
#define CORE_ATOMIC_H

#include "core_types.h"

typedef enum AtomicMemoryOrder
{
    ATOMIC_MEMORY_ORDER_RELAXED = 0,
    ATOMIC_MEMORY_ORDER_CONSUME,
    ATOMIC_MEMORY_ORDER_ACQUIRE,
    ATOMIC_MEMORY_ORDER_RELEASE,
    ATOMIC_MEMORY_ORDER_ACQ_REL,
    ATOMIC_MEMORY_ORDER_SEQ_CST,
} AtomicMemoryOrder;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_ATOMICS__)
    #include <stdatomic.h>
    #define CORE_ATOMIC_BACKEND_STDATOMIC 1
    #define CORE_ATOMIC_BACKEND_MSVC_INTRINSICS 0
    #define CORE_ATOMIC_BACKEND_GNUC_ATOMICS 0
#elif defined(_MSC_VER)
    #define CORE_ATOMIC_BACKEND_STDATOMIC 0
    #define CORE_ATOMIC_BACKEND_MSVC_INTRINSICS 1
    #define CORE_ATOMIC_BACKEND_GNUC_ATOMICS 0
#elif defined(__GNUC__) || defined(__clang__)
    #define CORE_ATOMIC_BACKEND_STDATOMIC 0
    #define CORE_ATOMIC_BACKEND_MSVC_INTRINSICS 0
    #define CORE_ATOMIC_BACKEND_GNUC_ATOMICS 1
#else
    #error Unsupported compiler: core_atomic requires C11 atomics, MSVC intrinsics, or GNU/Clang __atomic builtins.
#endif

typedef struct AtomicU32
{
#if CORE_ATOMIC_BACKEND_STDATOMIC
    _Atomic(u32) value;
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    volatile u32 value;
#else
    volatile u32 value;
#endif
} AtomicU32;

typedef struct AtomicU64
{
#if CORE_ATOMIC_BACKEND_STDATOMIC
    _Atomic(u64) value;
#elif CORE_ATOMIC_BACKEND_MSVC_INTRINSICS
    volatile u64 value;
#else
    volatile u64 value;
#endif
} AtomicU64;

void Atomic_ThreadFence (AtomicMemoryOrder order);
void Atomic_SignalFence (AtomicMemoryOrder order);

void AtomicU32_Init (AtomicU32 *atomic, u32 value);
u32 AtomicU32_Load (const AtomicU32 *atomic, AtomicMemoryOrder order);
void AtomicU32_Store (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order);
u32 AtomicU32_Exchange (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order);
b32 AtomicU32_CompareExchange (AtomicU32 *atomic, u32 *expected, u32 desired, AtomicMemoryOrder success_order, AtomicMemoryOrder failure_order);
u32 AtomicU32_FetchAdd (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order);
u32 AtomicU32_FetchSub (AtomicU32 *atomic, u32 value, AtomicMemoryOrder order);

void AtomicU64_Init (AtomicU64 *atomic, u64 value);
u64 AtomicU64_Load (const AtomicU64 *atomic, AtomicMemoryOrder order);
void AtomicU64_Store (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order);
u64 AtomicU64_Exchange (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order);
b32 AtomicU64_CompareExchange (AtomicU64 *atomic, u64 *expected, u64 desired, AtomicMemoryOrder success_order, AtomicMemoryOrder failure_order);
u64 AtomicU64_FetchAdd (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order);
u64 AtomicU64_FetchSub (AtomicU64 *atomic, u64 value, AtomicMemoryOrder order);

#endif // CORE_ATOMIC_H
