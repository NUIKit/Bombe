//
//  BOMStack.h
//  Bombe
//
//  Created by Robert Widmann on 2/15/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_STACK__
#define __BOMBE_STACK__

#include <Bombe/BOMDefines.h>

#include <stdbool.h>
#include <stdlib.h>

typedef const struct __BOMStack * BOMStackRef;

BOMBE_EXPORT
BOMStackRef BOMStackNew(void);

BOMBE_EXPORT
void BOMStackFree(BOMStackRef stack);

BOMBE_EXPORT
void BOMStackPush(BOMStackRef stack, void *item);

BOMBE_EXPORT
void *BOMStackPop(BOMStackRef stack);

BOMBE_EXPORT
bool BOMStackIsEmpty(BOMStackRef stack);

BOMBE_EXPORT
int32_t BOMStackCount(BOMStackRef stack);

#endif
