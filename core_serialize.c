#include "core_serialize.h"

ByteReader ByteReader_Create (void *data, usize size)
{
    return ByteReader_FromSlice(ByteSlice_FromMemory(data, size));
}

ByteReader ByteReader_FromSlice (ByteSlice bytes)
{
    ByteReader result;

    result.bytes = bytes;
    result.position = 0;
    return result;
}

b32 ByteReader_IsAtEnd (ByteReader reader)
{
    return reader.position >= reader.bytes.count;
}

usize ByteReader_GetRemaining (ByteReader reader)
{
    ASSERT(reader.position <= reader.bytes.count);

    return reader.bytes.count - reader.position;
}

b32 ByteReader_Skip (ByteReader *reader, usize size)
{
    ASSERT(reader != NULL);

    if (ByteReader_GetRemaining(*reader) < size)
    {
        return false;
    }

    reader->position += size;
    return true;
}

b32 ByteReader_ReadBytes (ByteReader *reader, void *destination, usize size)
{
    ASSERT(reader != NULL);

    if (ByteReader_GetRemaining(*reader) < size)
    {
        return false;
    }

    Memory_Copy(destination, reader->bytes.data + reader->position, size);
    reader->position += size;
    return true;
}

b32 ByteReader_ReadU8 (ByteReader *reader, u8 *value)
{
    return ByteReader_ReadBytes(reader, value, sizeof(*value));
}

b32 ByteReader_ReadU16 (ByteReader *reader, ByteOrder byte_order, u16 *value)
{
    u8 bytes[2];

    if (!ByteReader_ReadBytes(reader, bytes, sizeof(bytes)))
    {
        return false;
    }

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        *value = ((u16) bytes[0]) | ((u16) bytes[1] << 8);
    }
    else
    {
        *value = ((u16) bytes[0] << 8) | ((u16) bytes[1]);
    }

    return true;
}

b32 ByteReader_ReadU32 (ByteReader *reader, ByteOrder byte_order, u32 *value)
{
    u8 bytes[4];

    if (!ByteReader_ReadBytes(reader, bytes, sizeof(bytes)))
    {
        return false;
    }

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        *value = ((u32) bytes[0])        |
                 ((u32) bytes[1] << 8)   |
                 ((u32) bytes[2] << 16)  |
                 ((u32) bytes[3] << 24);
    }
    else
    {
        *value = ((u32) bytes[0] << 24)  |
                 ((u32) bytes[1] << 16)  |
                 ((u32) bytes[2] << 8)   |
                 ((u32) bytes[3]);
    }

    return true;
}

b32 ByteReader_ReadU64 (ByteReader *reader, ByteOrder byte_order, u64 *value)
{
    u8 bytes[8];

    if (!ByteReader_ReadBytes(reader, bytes, sizeof(bytes)))
    {
        return false;
    }

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        *value = ((u64) bytes[0])        |
                 ((u64) bytes[1] << 8)   |
                 ((u64) bytes[2] << 16)  |
                 ((u64) bytes[3] << 24)  |
                 ((u64) bytes[4] << 32)  |
                 ((u64) bytes[5] << 40)  |
                 ((u64) bytes[6] << 48)  |
                 ((u64) bytes[7] << 56);
    }
    else
    {
        *value = ((u64) bytes[0] << 56)  |
                 ((u64) bytes[1] << 48)  |
                 ((u64) bytes[2] << 40)  |
                 ((u64) bytes[3] << 32)  |
                 ((u64) bytes[4] << 24)  |
                 ((u64) bytes[5] << 16)  |
                 ((u64) bytes[6] << 8)   |
                 ((u64) bytes[7]);
    }

    return true;
}

b32 ByteReader_ReadI16 (ByteReader *reader, ByteOrder byte_order, i16 *value)
{
    return ByteReader_ReadU16(reader, byte_order, (u16 *) value);
}

b32 ByteReader_ReadI32 (ByteReader *reader, ByteOrder byte_order, i32 *value)
{
    return ByteReader_ReadU32(reader, byte_order, (u32 *) value);
}

b32 ByteReader_ReadI64 (ByteReader *reader, ByteOrder byte_order, i64 *value)
{
    return ByteReader_ReadU64(reader, byte_order, (u64 *) value);
}

ByteWriter ByteWriter_Create (void *data, usize size)
{
    return ByteWriter_FromSlice(ByteSlice_FromMemory(data, size));
}

ByteWriter ByteWriter_FromSlice (ByteSlice bytes)
{
    ByteWriter result;

    result.bytes = bytes;
    result.position = 0;
    return result;
}

b32 ByteWriter_IsAtEnd (ByteWriter writer)
{
    return writer.position >= writer.bytes.count;
}

usize ByteWriter_GetRemaining (ByteWriter writer)
{
    ASSERT(writer.position <= writer.bytes.count);

    return writer.bytes.count - writer.position;
}

b32 ByteWriter_Skip (ByteWriter *writer, usize size)
{
    ASSERT(writer != NULL);

    if (ByteWriter_GetRemaining(*writer) < size)
    {
        return false;
    }

    writer->position += size;
    return true;
}

b32 ByteWriter_WriteBytes (ByteWriter *writer, const void *source, usize size)
{
    ASSERT(writer != NULL);

    if (ByteWriter_GetRemaining(*writer) < size)
    {
        return false;
    }

    Memory_Copy(writer->bytes.data + writer->position, source, size);
    writer->position += size;
    return true;
}

b32 ByteWriter_WriteU8 (ByteWriter *writer, u8 value)
{
    return ByteWriter_WriteBytes(writer, &value, sizeof(value));
}

b32 ByteWriter_WriteU16 (ByteWriter *writer, ByteOrder byte_order, u16 value)
{
    u8 bytes[2];

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        bytes[0] = (u8) (value & 0xFFu);
        bytes[1] = (u8) ((value >> 8) & 0xFFu);
    }
    else
    {
        bytes[0] = (u8) ((value >> 8) & 0xFFu);
        bytes[1] = (u8) (value & 0xFFu);
    }

    return ByteWriter_WriteBytes(writer, bytes, sizeof(bytes));
}

b32 ByteWriter_WriteU32 (ByteWriter *writer, ByteOrder byte_order, u32 value)
{
    u8 bytes[4];

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        bytes[0] = (u8) (value & 0xFFu);
        bytes[1] = (u8) ((value >> 8) & 0xFFu);
        bytes[2] = (u8) ((value >> 16) & 0xFFu);
        bytes[3] = (u8) ((value >> 24) & 0xFFu);
    }
    else
    {
        bytes[0] = (u8) ((value >> 24) & 0xFFu);
        bytes[1] = (u8) ((value >> 16) & 0xFFu);
        bytes[2] = (u8) ((value >> 8) & 0xFFu);
        bytes[3] = (u8) (value & 0xFFu);
    }

    return ByteWriter_WriteBytes(writer, bytes, sizeof(bytes));
}

b32 ByteWriter_WriteU64 (ByteWriter *writer, ByteOrder byte_order, u64 value)
{
    u8 bytes[8];

    if (byte_order == BYTE_ORDER_LITTLE_ENDIAN)
    {
        bytes[0] = (u8) (value & 0xFFull);
        bytes[1] = (u8) ((value >> 8) & 0xFFull);
        bytes[2] = (u8) ((value >> 16) & 0xFFull);
        bytes[3] = (u8) ((value >> 24) & 0xFFull);
        bytes[4] = (u8) ((value >> 32) & 0xFFull);
        bytes[5] = (u8) ((value >> 40) & 0xFFull);
        bytes[6] = (u8) ((value >> 48) & 0xFFull);
        bytes[7] = (u8) ((value >> 56) & 0xFFull);
    }
    else
    {
        bytes[0] = (u8) ((value >> 56) & 0xFFull);
        bytes[1] = (u8) ((value >> 48) & 0xFFull);
        bytes[2] = (u8) ((value >> 40) & 0xFFull);
        bytes[3] = (u8) ((value >> 32) & 0xFFull);
        bytes[4] = (u8) ((value >> 24) & 0xFFull);
        bytes[5] = (u8) ((value >> 16) & 0xFFull);
        bytes[6] = (u8) ((value >> 8) & 0xFFull);
        bytes[7] = (u8) (value & 0xFFull);
    }

    return ByteWriter_WriteBytes(writer, bytes, sizeof(bytes));
}

b32 ByteWriter_WriteI16 (ByteWriter *writer, ByteOrder byte_order, i16 value)
{
    return ByteWriter_WriteU16(writer, byte_order, (u16) value);
}

b32 ByteWriter_WriteI32 (ByteWriter *writer, ByteOrder byte_order, i32 value)
{
    return ByteWriter_WriteU32(writer, byte_order, (u32) value);
}

b32 ByteWriter_WriteI64 (ByteWriter *writer, ByteOrder byte_order, i64 value)
{
    return ByteWriter_WriteU64(writer, byte_order, (u64) value);
}

u16 ByteSwapU16 (u16 value)
{
    return (u16) ((value >> 8) | (value << 8));
}

u32 ByteSwapU32 (u32 value)
{
    return ((value & 0x000000FFu) << 24) |
           ((value & 0x0000FF00u) << 8)  |
           ((value & 0x00FF0000u) >> 8)  |
           ((value & 0xFF000000u) >> 24);
}

u64 ByteSwapU64 (u64 value)
{
    return ((value & 0x00000000000000FFull) << 56) |
           ((value & 0x000000000000FF00ull) << 40) |
           ((value & 0x0000000000FF0000ull) << 24) |
           ((value & 0x00000000FF000000ull) << 8)  |
           ((value & 0x000000FF00000000ull) >> 8)  |
           ((value & 0x0000FF0000000000ull) >> 24) |
           ((value & 0x00FF000000000000ull) >> 40) |
           ((value & 0xFF00000000000000ull) >> 56);
}
