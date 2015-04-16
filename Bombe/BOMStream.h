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

typedef enum {
	BOMStreamByteOrderNone			= 0,
	BOMStreamByteOrderLittleEndian	= 1,
	BOMStreamByteOrderBigEndian		= 2,
} BOMStreamByteOrder;


typedef enum {
	BOMStreamTypeBlockID	= 0,
	BOMStreamTypeFile		= 1,
	BOMStreamTypeBuffer		= 2,
} BOMStreamType;

typedef struct __BOMStream * const BOMStreamRef;

BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithBuffer(void *buffer, size_t size);

BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithFileDescriptor(int fd, size_t size);

BOMBE_EXPORT
BOMStreamRef BOMStreamCreateWithBlockID(BOMStoreRef sto, BOMVar var, uint32_t blockID);

BOMBE_EXPORT
bool BOMStreamFlush(BOMStreamRef stream);

BOMBE_EXPORT
void BOMStreamFree(BOMStreamRef stream);

BOMBE_EXPORT
BOMStreamByteOrder BOMStreamGetByteOrder(BOMStreamRef stream);


BOMBE_EXPORT
bool BOMStreamRead(BOMStreamRef str, void *ptr, size_t size);

BOMBE_EXPORT
bool BOMStreamWrite(BOMStreamRef str, const void *buf, size_t size);

BOMBE_EXPORT
bool BOMStreamAdvance(BOMStreamRef str, size_t offset);

BOMBE_EXPORT
bool BOMStreamSeek(BOMStreamRef str, size_t pos, size_t offset);


BOMBE_EXPORT
bool BOMStreamReadUInt8(BOMStreamRef stream, uint8_t *to);

BOMBE_EXPORT
bool BOMStreamReadInt8(BOMStreamRef stream, int8_t *to);

BOMBE_EXPORT
bool BOMStreamReadUInt16(BOMStreamRef stream, uint16_t *to);

BOMBE_EXPORT
bool BOMStreamReadInt16(BOMStreamRef stream, int16_t *to);

BOMBE_EXPORT
bool BOMStreamReadUInt32(BOMStreamRef stream, uint32_t *to);

BOMBE_EXPORT
bool BOMStreamReadInt32(BOMStreamRef stream, int32_t *to);

BOMBE_EXPORT
bool BOMStreamReadUInt64(BOMStreamRef stream, uint64_t *to);

BOMBE_EXPORT
bool BOMStreamReadInt64(BOMStreamRef stream, int64_t *to);

BOMBE_EXPORT
bool BOMStreamReadFloat(BOMStreamRef stream, float *to);

BOMBE_EXPORT
bool BOMStreamReadDouble(BOMStreamRef stream, double *to);


BOMBE_EXPORT
bool BOMStreamWriteUInt8(BOMStreamRef stream, const uint8_t from);

BOMBE_EXPORT
bool BOMStreamWriteInt8(BOMStreamRef stream, const int8_t from);

BOMBE_EXPORT
bool BOMStreamWriteUInt16(BOMStreamRef stream, const uint16_t from);

BOMBE_EXPORT
bool BOMStreamWriteInt16(BOMStreamRef stream, const int16_t from);

BOMBE_EXPORT
bool BOMStreamWriteUInt32(BOMStreamRef stream, const uint32_t from);

BOMBE_EXPORT
bool BOMStreamWriteInt32(BOMStreamRef stream, const int32_t from);

BOMBE_EXPORT
bool BOMStreamWriteUInt64(BOMStreamRef stream, const uint64_t from);

BOMBE_EXPORT
bool BOMStreamWriteInt64(BOMStreamRef stream, const int64_t from);

BOMBE_EXPORT
bool BOMStreamWriteFloat(BOMStreamRef stream, const float from);

BOMBE_EXPORT
bool BOMStreamWriteDouble(BOMStreamRef stream, const double from);

#endif
