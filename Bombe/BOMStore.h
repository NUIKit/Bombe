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
#include <stdlib.h>

typedef const struct __BOMStore * BOMStoreRef;

typedef struct __BOMStore * BOMMutableStoreRef;

typedef struct __BOMBlock {
	uint32_t index;
	uint32_t size;
} BOMBlock;

typedef struct __BOMVar {
	uint32_t index;
	uint8_t length;
	char *name;
} BOMVar;

BOMBE_EXPORT
BOMStoreRef BOMStoreCreateWithPath(const char *path);

BOMBE_EXPORT
void BOMStoreFree(BOMStoreRef store);

BOMBE_EXPORT
void *BOMStoreCopyBlockData(BOMStoreRef sto, BOMVar var);

BOMBE_EXPORT
bool BOMStoreGetVarWithName(BOMStoreRef sto, const char *name, BOMVar *outVar);

#endif
