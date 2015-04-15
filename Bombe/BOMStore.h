//
//  BOMStore.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_STORE__
#define __BOMBE_STORE__

#include <Bombe/BOMDefines.h>
#include <stdbool.h>

typedef const struct __BOMStore * BOMStoreRef;

typedef struct __BOMStore * BOMMutableStoreRef;

typedef struct {
	int index;
	int size;
	char *name;
} BOMBlock;

BOMBE_EXPORT
BOMStoreRef BOMStoreCreateWithPath(const char *path);

BOMBE_EXPORT
void BOMStoreFree(BOMStoreRef store);

BOMBE_EXPORT
bool BOMStoreGetBlockWithName(BOMStoreRef store, const char *name, BOMBlock *outBlock);

#endif
