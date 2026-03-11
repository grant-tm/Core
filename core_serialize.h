#ifndef CORE_SERIALIZE_H
#define CORE_SERIALIZE_H

#include "core_bits.h"

typedef enum ByteOrder
{
    BYTE_ORDER_LITTLE_ENDIAN = 0,
    BYTE_ORDER_BIG_ENDIAN,
} ByteOrder;

typedef struct ByteReader
{
    ByteSlice bytes;
    usize position;
} ByteReader;

typedef struct ByteWriter
{
    ByteSlice bytes;
    usize position;
} ByteWriter;

ByteReader ByteReader_Create (void *data, usize size);
ByteReader ByteReader_FromSlice (ByteSlice bytes);
b32 ByteReader_IsAtEnd (ByteReader reader);
usize ByteReader_GetRemaining (ByteReader reader);
b32 ByteReader_Skip (ByteReader *reader, usize size);
b32 ByteReader_ReadBytes (ByteReader *reader, void *destination, usize size);
b32 ByteReader_ReadU8 (ByteReader *reader, u8 *value);
b32 ByteReader_ReadU16 (ByteReader *reader, ByteOrder byte_order, u16 *value);
b32 ByteReader_ReadU32 (ByteReader *reader, ByteOrder byte_order, u32 *value);
b32 ByteReader_ReadU64 (ByteReader *reader, ByteOrder byte_order, u64 *value);
b32 ByteReader_ReadI16 (ByteReader *reader, ByteOrder byte_order, i16 *value);
b32 ByteReader_ReadI32 (ByteReader *reader, ByteOrder byte_order, i32 *value);
b32 ByteReader_ReadI64 (ByteReader *reader, ByteOrder byte_order, i64 *value);

ByteWriter ByteWriter_Create (void *data, usize size);
ByteWriter ByteWriter_FromSlice (ByteSlice bytes);
b32 ByteWriter_IsAtEnd (ByteWriter writer);
usize ByteWriter_GetRemaining (ByteWriter writer);
b32 ByteWriter_Skip (ByteWriter *writer, usize size);
b32 ByteWriter_WriteBytes (ByteWriter *writer, const void *source, usize size);
b32 ByteWriter_WriteU8 (ByteWriter *writer, u8 value);
b32 ByteWriter_WriteU16 (ByteWriter *writer, ByteOrder byte_order, u16 value);
b32 ByteWriter_WriteU32 (ByteWriter *writer, ByteOrder byte_order, u32 value);
b32 ByteWriter_WriteU64 (ByteWriter *writer, ByteOrder byte_order, u64 value);
b32 ByteWriter_WriteI16 (ByteWriter *writer, ByteOrder byte_order, i16 value);
b32 ByteWriter_WriteI32 (ByteWriter *writer, ByteOrder byte_order, i32 value);
b32 ByteWriter_WriteI64 (ByteWriter *writer, ByteOrder byte_order, i64 value);

u16 ByteSwapU16 (u16 value);
u32 ByteSwapU32 (u32 value);
u64 ByteSwapU64 (u64 value);

#endif // CORE_SERIALIZE_H
