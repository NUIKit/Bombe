//
//  BOMStore.c
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#include "BOMStore.h"
#include "BOMStream.h"
#include "Internal.h"

typedef struct {
	uint32_t unknown;
	uint32_t indexOffset;
	uint32_t indexLength;
	uint32_t tocOffset;
	uint32_t tocSize;
} BOMHeader;

struct __BOMStore {
	BOMHeader header;
	void *mmapAddr;
	size_t mmapSize;

	int32_t blockCount;
	BOMBlock *blockTable;
	ssize_t blockTableSize;
};

static void BOMStoreCreateBlockTable(BOMStoreRef);
static bool BOMReadBlockTable(BOMStoreRef, BOMStreamRef);
static void BOMExpandBlockTable(BOMStoreRef, size_t);

BOMStoreRef BOMStoreCreateWithPath(const char *path) {
	int fd = open(path, O_NOFOLLOW | O_NONBLOCK | O_TRUNC);
	if (fd == -1) {
		return NULL;
	}
	
	struct stat stat;
	if (fstat(fd, &stat) == -1) {
		close(fd);
		return NULL;
	}
	
	BOMStreamRef stream = BOMStreamCreateWithFileDescriptor(fd, stat.st_size);
	if (stream == NULL) {
		close(fd);
		return NULL;
	}
	
	uint32_t head1, head2;
	BOMStreamReadUInt32(stream, &head1);
	BOMStreamReadUInt32(stream, &head2);

	// All BOM files begin with `BOMStore`
	if ((head1 != 'BOMS') || (head2 != 'tore')) {
		BOMStreamFree(stream);
		return NULL;
	}
	
	uint32_t version;
	BOMStreamReadUInt32(stream, &version);
	
	// We only read version 1.
	if (version != 1) {
//		fprintf(stderr, "%s has an unknown version: 0x%X\n", path, version);
	}
	
	struct __BOMStore *store = malloc(sizeof(struct __BOMStore));
	if (store == NULL) {
		BOMStreamFree(stream);
		return NULL;
	}
	
	// Read in the header.
	BOMStreamReadUInt32(stream, &store->header.unknown);
	BOMStreamReadUInt32(stream, &store->header.indexOffset);
	BOMStreamReadUInt32(stream, &store->header.indexLength);
	BOMStreamReadUInt32(stream, &store->header.tocOffset);
	BOMStreamReadUInt32(stream, &store->header.tocSize);
	BOMStreamFree(stream);
	
	/// mmap in the BOM file.
	if ((store->mmapAddr = mmap(NULL, stat.st_size, PROT_READ, MAP_ANON | MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		BOMStoreFree(store);
		return NULL;
	}
	
	BOMStoreCreateBlockTable(store);
	BOMStreamRef indexStream = BOMStreamCreateWithBuffer(store->mmapAddr + store->header.indexOffset, store->header.indexLength);
	
	if (indexStream == NULL) {
		BOMStoreFree(store);
		return NULL;
	}
	
	BOMStreamFree(indexStream);
	
	BOMStreamRef blockStream = BOMStreamCreateWithBuffer(store->mmapAddr + store->header.indexOffset, store->header.indexLength);
	if (BOMReadBlockTable(store, blockStream) == false) {
		BOMStoreFree(store);
		return NULL;
	}
	
	return store;
}

void BOMStoreFree(BOMStoreRef sto) {
	struct __BOMStore *store = (struct __BOMStore *)sto;
	if (store != NULL) {
		if (store->blockTable != 0) {
			if (vm_deallocate(mach_task_self(), (vm_address_t)store->blockTable, store->blockTableSize) != KERN_SUCCESS) {
//				BOMAssert("vm_deallocate failed");
			}
		}
		if (store->mmapSize != 0x0) {
			if (munmap(store->mmapAddr, store->mmapSize) == -1) {
//				BOMAssert("munmap failed");
			}
		}
		free(store);
	}
}

bool BOMStoreGetBlockWithName(BOMStoreRef sto, const char *name, BOMBlock *outBlock) {
	struct __BOMStore *store = (struct __BOMStore *)sto;

	if (name == NULL) {
		return NULL;
	}
	
	if (store->header.tocOffset == 0 || store->header.tocSize == 0) {
		return NULL;
	}

	BOMStreamRef stream = BOMStreamCreateWithBuffer(store->mmapAddr + store->header.tocOffset, store->header.tocSize);
	if (stream == NULL) {
		return NULL;
	}
	
	uint32_t contentsCount;
	BOMStreamReadUInt32(stream, &contentsCount);

	if (contentsCount == 0) {
		BOMStreamFree(stream);
		return NULL;
	}
	for (size_t i = 0; i < contentsCount; i++) {
		uint32_t index;
		BOMStreamReadUInt32(stream, &index);
		uint8_t nameLen;
		BOMStreamReadUInt8(stream, &nameLen);
		
		char buf[nameLen];
		BOMStreamRead(stream, buf, nameLen);
		if (strcmp(buf, name) == 0) {
			BOMStreamFree(stream);
			*outBlock = (BOMBlock){ index, nameLen, buf };
		}		
	}
	BOMStreamFree(stream);
	return outBlock != NULL;
}

static void BOMStoreCreateBlockTable(BOMStoreRef sto) {
	struct __BOMStore *store = (struct __BOMStore *)sto;
	if (store != 0x0) {
		size_t size = PAGE_SIZE;
		if (size % vm_page_size != 0) {
			size += vm_page_size - (size % vm_page_size);
		}
		if (vm_allocate(mach_task_self(), (vm_address_t *)&store->blockTable, size, 0x1) != KERN_SUCCESS) {
			store->blockTable = 0;
		}
		store->blockTableSize = size;
	}
}

static bool BOMReadBlockTable(BOMStoreRef st, BOMStreamRef arg1) {
	struct __BOMStore *store = (struct __BOMStore *)st;
	uint32_t count;
	BOMStreamReadUInt32(arg1, &count);
	
	if (count != 0x0) {
		if ((count > 0x1fffffff) || ((count << 0x3) > store->header.indexLength)) {
			fwrite("bad value for block table count\n", 0x20, 0x1, stderr);
			return false;
		}
		BOMExpandBlockTable(st, count * sizeof(BOMBlock));
		if (store->blockTable != 0) {
			store->blockCount = count;
			for (size_t i = 0; i < count; i++) {
				BOMBlock block;
				uint32_t index, size;
				BOMStreamReadUInt32(arg1, &index);
				BOMStreamReadUInt32(arg1, &size);
				block.index = index;
				block.size = size;
				BOMStreamAdvance(arg1, sizeof(BOMBlock) + block.size);
				store->blockTable[i] = block;
			}
		}
	}
	return true;
}

static void BOMExpandBlockTable(BOMStoreRef st, vm_size_t newSize) {
	struct __BOMStore *store = (struct __BOMStore *)st;
	
	if (store->blockTableSize < newSize) {
		vm_size_t size = newSize;
		if (size % vm_page_size != 0x0) {
			size = (vm_page_size + size) - (size % vm_page_size);
		}
		BOMBlock *reallocAddr;
		if (vm_allocate(mach_task_self(), (vm_address_t *)&reallocAddr, size, VM_FLAGS_ANYWHERE) != KERN_SUCCESS) {
//			BOMAssert("vm_allocate failed");
		}
		if (vm_copy(mach_task_self(), (vm_address_t)store->blockTable, store->blockTableSize, (vm_address_t)reallocAddr) != KERN_SUCCESS) {
//			BOMAssert("vm_copy failed");
		}
		if (vm_deallocate(mach_task_self(), (vm_address_t)store->blockTable, store->blockTableSize) != KERN_SUCCESS) {
//			BOMAssert("vm_deallocate failed");
		}
		store->blockTable = reallocAddr;
		store->blockTableSize = newSize;
	}
}
