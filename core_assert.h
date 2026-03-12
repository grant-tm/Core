#ifndef CORE_ASSERT_H
#define CORE_ASSERT_H

#include <stdlib.h>

#include "core_base.h"

#ifndef CORE_ASSERTS_ENABLED
    #if defined(CORE_ENABLE_ASSERTS)
        #define CORE_ASSERTS_ENABLED 1
    #elif defined(CORE_DISABLE_ASSERTS)
        #define CORE_ASSERTS_ENABLED 0
    #elif defined(NDEBUG)
        #define CORE_ASSERTS_ENABLED 0
    #else
        #define CORE_ASSERTS_ENABLED 1
    #endif
#endif

typedef void CoreAssertHandler (const char *expression, const char *message, const char *file, i32 line);

void Core_SetAssertHandler (CoreAssertHandler *handler);
CoreAssertHandler *Core_GetAssertHandler (void);
void Core_AssertFailure (const char *expression, const char *message, const char *file, i32 line);

#if CORE_ASSERTS_ENABLED
    #define ASSERT(expression) \
        do \
        { \
            if (!(expression)) \
            { \
                Core_AssertFailure(#expression, NULL, __FILE__, (i32) __LINE__); \
            } \
        } while (0)

    #define ASSERT_MESSAGE(expression, message) \
        do \
        { \
            if (!(expression)) \
            { \
                Core_AssertFailure(#expression, (message), __FILE__, (i32) __LINE__); \
            } \
        } while (0)

    #define INVALID_CODE_PATH() \
        Core_AssertFailure("INVALID_CODE_PATH()", "Invalid code path reached.", __FILE__, (i32) __LINE__)

    #define NOT_IMPLEMENTED() \
        Core_AssertFailure("NOT_IMPLEMENTED()", "Feature is not implemented.", __FILE__, (i32) __LINE__)

    #define UNREACHABLE() \
        Core_AssertFailure("UNREACHABLE()", "Unreachable code reached.", __FILE__, (i32) __LINE__)
#else
    #define ASSERT(expression) ((void) sizeof(expression))
    #define ASSERT_MESSAGE(expression, message) ((void) sizeof(expression), (void) sizeof(message))
    #define INVALID_CODE_PATH() ((void) 0)
    #define NOT_IMPLEMENTED() ((void) 0)
    #define UNREACHABLE() ((void) 0)
#endif

#endif // CORE_ASSERT_H
