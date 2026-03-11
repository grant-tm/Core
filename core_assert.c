#include <stdio.h>
#include <stdlib.h>

#include "core_assert.h"

static void Core_DefaultAssertHandler (const char *expression, const char *message, const char *file, i32 line)
{
    if (message != NULL)
    {
        fprintf(stderr, "ASSERT FAILED: %s\nMessage: %s\nLocation: %s:%d\n", expression, message, file, line);
    }
    else
    {
        fprintf(stderr, "ASSERT FAILED: %s\nLocation: %s:%d\n", expression, file, line);
    }
}

static CoreAssertHandler *core_assert_handler = Core_DefaultAssertHandler;

void Core_SetAssertHandler (CoreAssertHandler *handler)
{
    core_assert_handler = (handler != NULL) ? handler : Core_DefaultAssertHandler;
}

CoreAssertHandler *Core_GetAssertHandler (void)
{
    return core_assert_handler;
}

void Core_AssertFailure (const char *expression, const char *message, const char *file, i32 line)
{
    core_assert_handler(expression, message, file, line);
    abort();
}
