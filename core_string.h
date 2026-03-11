#ifndef CORE_STRING_H
#define CORE_STRING_H

#include "core_memory.h"

#define StringLiteral(value) ((String) {(c8 *) (value), sizeof(value) - 1})

typedef struct String
{
    c8 *data;
    usize count;
} String;

usize CString_Length (const c8 *c_string);
i32 CString_Compare (const c8 *left, const c8 *right);

String String_Create (c8 *data, usize count);
String String_FromCString (c8 *c_string);
b32 String_IsEmpty (String string);
b32 String_Equals (String left, String right);
b32 String_EqualsCString (String left, const c8 *right);
String String_Slice (String string, usize start_index, usize count);
String String_Prefix (String string, usize count);
String String_Suffix (String string, usize count);
usize String_FindChar (String string, c8 character);
usize String_FindString (String string, String value);
b32 String_StartsWith (String string, String prefix);
b32 String_EndsWith (String string, String suffix);
String String_TrimLeftWhitespace (String string);
String String_TrimRightWhitespace (String string);
String String_TrimWhitespace (String string);

#endif // CORE_STRING_H
