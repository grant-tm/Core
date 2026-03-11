#include <string.h>

#include "core_string.h"

static b32 CharIsWhitespace (c8 character)
{
    return (character == ' ')  ||
           (character == '\t') ||
           (character == '\n') ||
           (character == '\r') ||
           (character == '\v') ||
           (character == '\f');
}

usize CString_Length (const c8 *c_string)
{
    ASSERT(c_string != NULL);

    return (usize) strlen(c_string);
}

i32 CString_Compare (const c8 *left, const c8 *right)
{
    ASSERT(left != NULL);
    ASSERT(right != NULL);

    return strcmp(left, right);
}

String String_Create (c8 *data, usize count)
{
    String result;

    if (count > 0)
    {
        ASSERT(data != NULL);
    }

    result.data = data;
    result.count = count;
    return result;
}

String String_FromLiteral (StringLiteral literal)
{
    return String_Create((c8 *) literal.data, literal.count);
}

String String_FromCString (c8 *c_string)
{
    if (c_string == NULL)
    {
        return String_Create(NULL, 0);
    }

    return String_Create(c_string, CString_Length(c_string));
}

b32 String_IsEmpty (String string)
{
    return string.count == 0;
}

b32 String_Equals (String left, String right)
{
    if (left.count != right.count)
    {
        return false;
    }

    if (left.count == 0)
    {
        return true;
    }

    return Memory_Compare(left.data, right.data, left.count) == 0;
}

b32 String_EqualsCString (String left, const c8 *right)
{
    String right_string;

    ASSERT(right != NULL);

    right_string.data = (c8 *) right;
    right_string.count = CString_Length(right);
    return String_Equals(left, right_string);
}

String String_Slice (String string, usize start_index, usize count)
{
    ASSERT(start_index <= string.count);
    ASSERT(count <= (string.count - start_index));

    return String_Create(string.data + start_index, count);
}

String String_Prefix (String string, usize count)
{
    ASSERT(count <= string.count);

    return String_Slice(string, 0, count);
}

String String_Suffix (String string, usize count)
{
    ASSERT(count <= string.count);

    return String_Slice(string, string.count - count, count);
}

usize String_FindChar (String string, c8 character)
{
    usize index;

    for (index = 0; index < string.count; index += 1)
    {
        if (string.data[index] == character)
        {
            return index;
        }
    }

    return string.count;
}

usize String_FindString (String string, String value)
{
    usize index;

    if (value.count == 0)
    {
        return 0;
    }

    if (value.count > string.count)
    {
        return string.count;
    }

    for (index = 0; index <= string.count - value.count; index += 1)
    {
        if (Memory_Compare(string.data + index, value.data, value.count) == 0)
        {
            return index;
        }
    }

    return string.count;
}

b32 String_StartsWith (String string, String prefix)
{
    if (prefix.count > string.count)
    {
        return false;
    }

    return String_Equals(String_Prefix(string, prefix.count), prefix);
}

b32 String_EndsWith (String string, String suffix)
{
    if (suffix.count > string.count)
    {
        return false;
    }

    return String_Equals(String_Suffix(string, suffix.count), suffix);
}

String String_TrimLeftWhitespace (String string)
{
    usize index;

    index = 0;
    while ((index < string.count) && CharIsWhitespace(string.data[index]))
    {
        index += 1;
    }

    return String_Slice(string, index, string.count - index);
}

String String_TrimRightWhitespace (String string)
{
    usize count;

    count = string.count;
    while ((count > 0) && CharIsWhitespace(string.data[count - 1]))
    {
        count -= 1;
    }

    return String_Prefix(string, count);
}

String String_TrimWhitespace (String string)
{
    return String_TrimRightWhitespace(String_TrimLeftWhitespace(string));
}
