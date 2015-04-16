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
#include "BOMStack.h"
#include "Internal.h"

#include <stdio.h>

typedef struct BOMTreeNode {
	uint32_t blockID;
	int16_t isLeaf;
	int32_t nextNode;
	int32_t previousNode;
	int16_t count;
	
	uint32_t *paths;
	uint32_t *files;
} *BOMTreeNodeRef;

struct __BOMTree {
	BOMStoreRef storage;
	char *path;
	BOMBlock block;
	uint32_t blockSize;
	uint32_t pathCount;
	uint8_t unknown;
	
	BOMTreeNodeRef rootNode;
};

static BOMTreeNodeRef BOMTreeNodeCreateWithBlockID(BOMTreeRef tree, uint32_t blockID);

BOMTreeRef BOMTreeCreateTraversingPath(BOMStoreRef store, const char *name) {
	if (store == NULL || name == NULL) {
		return NULL;
	}
	
	BOMBlock block;
	if (!BOMStoreGetBlockWithName(store, name, &block)) {
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
	
	uint32_t children, blockSize, pathCount;
	uint8_t unknown;
	BOMStreamReadUInt32(stream, &children);
	BOMStreamReadUInt32(stream, &blockSize);
	BOMStreamReadUInt32(stream, &pathCount);
	BOMStreamReadUInt8(stream, &unknown);

	tree->blockSize = blockSize;
	tree->pathCount = ntohl(pathCount);
	tree->unknown = unknown;
	
	BOMStreamFree(stream);
	
	tree->rootNode = BOMTreeNodeCreateWithBlockID(tree, children);
	
	return (BOMTreeRef)tree;
}

BOMTreeNodeRef BOMTreeNodeCreateWithBlockID(BOMTreeRef tree, uint32_t blockID) {
	uint32_t *pathBuf = malloc((tree->pathCount + 1) * sizeof(uint32_t));
	if (pathBuf == NULL) {
		return NULL;
	}
	
	
	uint32_t *filesBuf = malloc((tree->pathCount + 2) * sizeof(uint32_t));
	if (filesBuf == NULL) {
		free(pathBuf);
		return NULL;
	}
	
	struct BOMTreeNode *freshPage = calloc(1, sizeof(struct BOMTreeNode));
	if (freshPage == NULL) {
		free(filesBuf);		
		free(pathBuf);
		return NULL;
	}
	
	if (blockID == 0) {
		blockID = BOMStoreCreateNewBlock((BOMMutableStoreRef)tree->storage);
	}
	
	freshPage->paths = pathBuf;
	freshPage->files = filesBuf;
	freshPage->blockID = blockID;
	
	return freshPage;
}

void BOMTreeFree(BOMTreeRef tree) {
	if (tree == NULL) {
		return;
	}
	
	free(tree->path);
}
