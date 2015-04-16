//
//  BOMStream.c
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#include "BOMStream.h"
#include "Internal.h"

struct __BOMStream {
	int fd;
	uint32_t blockID;
	BOMStreamType type;
	BOMStreamByteOrder byteOrder;
	void *buf;
	size_t size;
	size_t pos;
	bool dirty;
};

BOMStreamRef BOMStreamCreateWithBuffer(void *buffer, size_t size) {
	if (buffer == NULL) {
		return NULL;
	}

	struct __BOMStream *stream = malloc(sizeof(struct __BOMStream));
	if (stream == NULL) {
		return NULL;
	}
	
	stream->fd = -1;
	stream->blockID = 0;
	stream->type = BOMStreamTypeBuffer;
	stream->byteOrder = BOMStreamByteOrderLittleEndian;
	stream->size = size;
	stream->buf = buffer;
	stream->pos = 0;
	stream->dirty = false;
	return stream;
}

BOMStreamRef BOMStreamCreateWithFileDescriptor(int fd, size_t size) {
	if (fd == -1) {
		return NULL;
	}
	
	struct __BOMStream *stream = malloc(sizeof(struct __BOMStream));
	if (stream == NULL) {
		return NULL;
	}
	
	void *buffer = malloc(size);
	if (buffer == NULL) {
		BOMStreamFree(stream);
		return NULL;
	}
	
	stream->fd = fd;
	stream->blockID = 0;
	stream->type = BOMStreamTypeFile;
	stream->byteOrder = BOMStreamByteOrderLittleEndian;
	stream->size = size;
	stream->buf = buffer;
	stream->pos = 0;
	stream->dirty = false;
	return stream;
}

BOMStreamRef BOMStreamCreateWithBlockID(BOMStoreRef sto, BOMBlock var, uint32_t blockID) {
	if (blockID == 0) {
		return NULL;
	}
	
	struct __BOMStream *stream = malloc(sizeof(struct __BOMStream));
	if (stream == NULL) {
		return NULL;
	}
	
	stream->fd = -1;
	stream->blockID = blockID;
	stream->type = BOMStreamTypeBlockID;
	stream->byteOrder = BOMStreamByteOrderLittleEndian;
	stream->size = 0;
	stream->buf = BOMStoreCopyBlockData(sto, var);
	stream->pos = 0;
	stream->dirty = false;
	return stream;
}

bool BOMStreamFlush(BOMStreamRef stream) {
	if (stream == NULL || (stream->dirty == false)) {
		return false;
	}
	
	if (stream->type == BOMStreamTypeFile) {
		if (lseek(stream->fd, 0, SEEK_SET) == -1) {
			return false;
		}
		
		if (write(stream->fd, stream->buf, stream->size) != stream->size) {
			return false;
		}
	}
	
	stream->dirty = false;

	return true;
}

void BOMStreamFree(BOMStreamRef stream) {
	if (stream == NULL) {
		return;
	}
	
	if (stream->type == BOMStreamTypeBuffer) {
		free(stream->buf);
		free(stream);
	} else if (stream->type == BOMStreamTypeFile) {
		close(stream->fd);
		free(stream->buf);
		free(stream);
	}
}

BOMStreamByteOrder BOMStreamGetByteOrder(BOMStreamRef stream) {
	if (stream == NULL) {
		return BOMStreamByteOrderNone;
	}
	return stream->byteOrder;
}

bool BOMStreamRead(BOMStreamRef str, void *ptr, size_t size) {
	struct __BOMStream *stream = (struct __BOMStream *)str;

	if (stream == NULL) {
		return false;
	}
	
	size_t newPosition = str->pos + size;
	if (stream->size <= newPosition) {
		return false;
	}
	
	memcpy(ptr, stream->buf, size);
	return BOMStreamSeek(str, size, str->pos);
}

bool BOMStreamWrite(BOMStreamRef str, const void *buf, size_t size) {
	struct __BOMStream *stream = (struct __BOMStream *)str;
	
	if (stream == NULL) {
		return false;
	}
	
	memcpy(stream->buf, buf, size);
	stream->dirty = true;
	
	return BOMStreamSeek(str, size, str->pos);
}

bool BOMStreamAdvance(BOMStreamRef str, size_t offset) {
	return BOMStreamSeek(str, str->pos, offset);
}

bool BOMStreamSeek(BOMStreamRef str, size_t pos, size_t offset) {
	struct __BOMStream *stream = (struct __BOMStream *)str;
	
	if (stream == NULL) {
		return false;
	}
	
	size_t newPosition = pos + offset;
	if (stream->size <= newPosition) {
		return false;
	}
	
	stream->pos = newPosition;
	return true;
}


bool BOMStreamReadUInt8(BOMStreamRef stream, uint8_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadInt8(BOMStreamRef stream, int8_t *to){
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadUInt16(BOMStreamRef stream, uint16_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadInt16(BOMStreamRef stream, int16_t *to){
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadUInt32(BOMStreamRef stream, uint32_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadInt32(BOMStreamRef stream, int32_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadUInt64(BOMStreamRef stream, uint64_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadInt64(BOMStreamRef stream, int64_t *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadFloat(BOMStreamRef stream, float *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}

bool BOMStreamReadDouble(BOMStreamRef stream, double *to) {
	return BOMStreamRead(stream, to, sizeof(*to));
}


bool BOMStreamWriteUInt8(BOMStreamRef stream, const uint8_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteInt8(BOMStreamRef stream, const int8_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteUInt16(BOMStreamRef stream, const uint16_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteInt16(BOMStreamRef stream, const int16_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteUInt32(BOMStreamRef stream, const uint32_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteInt32(BOMStreamRef stream, const int32_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteUInt64(BOMStreamRef stream, const uint64_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteInt64(BOMStreamRef stream, const int64_t from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteFloat(BOMStreamRef stream, const float from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}

bool BOMStreamWriteDouble(BOMStreamRef stream, const double from) {
	return BOMStreamWrite(stream, &from, sizeof(from));
}
