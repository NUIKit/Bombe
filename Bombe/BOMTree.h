//
//  BOMTree.h
//  Bombe
//
//  Created by Robert Widmann on 2/7/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_BOMTREE__
#define __BOMBE_BOMTREE__

#include <Bombe/BOMDefines.h>
#include <Bombe/BOMStore.h>

typedef struct __BOMTree * const BOMTreeRef;

BOMBE_EXPORT
BOMTreeRef BOMTreeCreateTraversingPath(BOMStoreRef store, const char *name);

BOMBE_EXPORT
void BOMTreeFree(BOMTreeRef tree);

#endif
