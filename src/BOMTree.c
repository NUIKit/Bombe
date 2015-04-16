//
//  BOMTree.c
//  Bombe
//
//  Created by Robert Widmann on 2/7/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#include "BOMTree.h"
#include "BOMStore.h"
#include "BOMStream.h"
#include "Internal.h"

#include <stdio.h>

struct BOMIndex {
	uint32_t address;
	uint32_t length;
} __attribute__((packed));

struct __BOMTree {
	BOMStoreRef storage;
	char *path;
	BOMVar block;
};

BOMTreeRef BOMTreeCreateTraversingPath(BOMStoreRef store, const char *name) {
	if (store == NULL || name == NULL) {
		return NULL;
	}
	
	BOMVar block;
	if (!BOMStoreGetVarWithName(store, name, &block)) {
		return NULL;
	}
	
	struct __BOMTree *tree = malloc(sizeof(struct __BOMTree));
	if (tree == NULL) {
		return NULL;
	}
	
	tree->storage = store;
	tree->block = block;
	
	if (name != NULL) {
		tree->path = strdup(name);
	}
	
	BOMStreamRef stream = BOMStreamCreateWithBlockID(store, block, 0);
	if (stream == NULL) {
		BOMTreeFree(tree);
		return NULL;
	}
	
	uint32_t magic;
	BOMStreamReadUInt32(stream, &magic);
	
	if (magic != 'tree') {
		BOMTreeFree(tree);
		return NULL;
	}
	
	uint32_t version;
	BOMStreamReadUInt32(stream, &version);
	
	if (version != 1) {
		BOMTreeFree(tree);
		return NULL;
	}
	
	return (BOMTreeRef)tree;
}

void BOMTreeFree(BOMTreeRef tree) {
	
}
