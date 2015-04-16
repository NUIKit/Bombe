//
//  BOMStream.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_STREAM__
#define __BOMBE_STREAM__

#include <Bombe/BOMDefines.h>
#include <Bombe/BOMStore.h>

#include <stdbool.h>
#include <stdlib.h>

/// The byte order a stream can have.
typedef enum {
	/// The stream's byte order is unknown.
	BOMStreamByteOrderNone			= 0,
	/// The stream is little endian.
	BOMStreamByteOrderLittleEndian	= 1,
	/// The stream is big endian.
	BOMStreamByteOrderBigEndian		= 2,
} BOMStreamByteOrder;

/// The types of bytes a stream represents. 
typedef enum {
	/// The stream represents a block ID in a BOM file.
	BOMStreamTypeBlockID	= 0,
	/// The stream represents a file.
	BOMStreamTypeFile		= 1,
	/// The stream represents a buffer.
	BOMStreamTypeBuffer		= 2,
} BOMStreamType;

/// The type of streams.
typedef struct __BOMStream * const BOMStreamRef;

/// Creates a stream that can traverse a buffer of a given size.
BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithBuffer(void *buffer, size_t size);

/// Creates a stream that can traverse the contents of a file of a given size.
BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithFileDescriptor(int fd, size_t size);

/// Creates a stream that can traverse the contents of a block.
BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithBlockID(BOMStoreRef sto, BOMBlock block, uint32_t blockID);

/// Writes the bytes from a stream that represent files to memory.
BOMBE_EXPORT
bool BOMStreamFlush(BOMStreamRef stream);

/// Frees a stream and its associated resources.
BOMBE_EXPORT
void BOMStreamFree(BOMStreamRef stream);

/// Gets the byte order of a stream.
BOMBE_EXPORT
BOMStreamByteOrder BOMStreamGetByteOrder(BOMStreamRef stream);


/// Reads a given amount of bytes from a stream into a buffer.
BOMBE_EXPORT
bool BOMStreamRead(BOMStreamRef str, void *ptr, size_t size);

/// Writes a given amount of bytes from a buffer into a stream.
BOMBE_EXPORT
bool BOMStreamWrite(BOMStreamRef str, const void *buf, size_t size);

/// Advances the offset of a stream by a given number of bytes.
BOMBE_EXPORT
bool BOMStreamAdvance(BOMStreamRef str, size_t offset);

/// Sets the pointer into the stream.
BOMBE_EXPORT
bool BOMStreamSeek(BOMStreamRef str, size_t pos, size_t offset);


/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadUInt8(BOMStreamRef stream, uint8_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadInt8(BOMStreamRef stream, int8_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadUInt16(BOMStreamRef stream, uint16_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadInt16(BOMStreamRef stream, int16_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadUInt32(BOMStreamRef stream, uint32_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadInt32(BOMStreamRef stream, int32_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadUInt64(BOMStreamRef stream, uint64_t *to);

/// Reads an integer from the stream.
BOMBE_EXPORT
bool BOMStreamReadInt64(BOMStreamRef stream, int64_t *to);

/// Reads a float from the stream.
BOMBE_EXPORT
bool BOMStreamReadFloat(BOMStreamRef stream, float *to);

/// Reads a double from the stream.
BOMBE_EXPORT
bool BOMStreamReadDouble(BOMStreamRef stream, double *to);


/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteUInt8(BOMStreamRef stream, const uint8_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteInt8(BOMStreamRef stream, const int8_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteUInt16(BOMStreamRef stream, const uint16_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteInt16(BOMStreamRef stream, const int16_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteUInt32(BOMStreamRef stream, const uint32_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteInt32(BOMStreamRef stream, const int32_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteUInt64(BOMStreamRef stream, const uint64_t from);

/// Writes an integer into the stream.
BOMBE_EXPORT
bool BOMStreamWriteInt64(BOMStreamRef stream, const int64_t from);

/// Writes a float into the stream.
BOMBE_EXPORT
bool BOMStreamWriteFloat(BOMStreamRef stream, const float from);

/// Writes a double into the stream.
BOMBE_EXPORT
bool BOMStreamWriteDouble(BOMStreamRef stream, const double from);

#endif
