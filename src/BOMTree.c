//
//  BOMTree.c
//  Bombe
//
//  Created by Robert Widmann on 2/7/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#include "BOMTree.h"
#include "BOMStore.h"
#include "Internal.h"

#include <stdio.h>

struct BOMIndex {
	uint32_t address;
	uint32_t length;
} __attribute__((packed));

struct __BOMTree {
	
};

BOMTreeRef BOMTreeCreateTraversingPath(BOMStoreRef store, const char *name) {
	if (store == NULL || name == NULL) {
		return NULL;
	}
	
	BOMBlock block;
	if (!BOMStoreGetBlockWithName(store, name, &block)) {
		return NULL;
	}
	
	struct __BOMTree *tree = malloc(sizeof(struct __BOMTree));
	
	return (BOMTreeRef)tree;
}

//void *BOMBlockGet(BOMBlock block, int32_t index, int32_t *outLength) {
//	BOMIndex *index = (indexHeader->index + ntohl(index));
//}
