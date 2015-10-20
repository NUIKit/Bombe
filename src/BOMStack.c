//
//  BOMStack.c
//  Bombe
//
//  Created by Robert Widmann on 2/15/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#include "BOMStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct __BOMStack {
	void **buf;
	int32_t maxSize;
	int32_t count;
};

BOMStackRef BOMStackNew(void) {
	struct __BOMStack *stack = malloc(sizeof(struct __BOMStack));
	if (stack != NULL) {
		stack->maxSize = 1024;
		stack->buf = malloc(stack->maxSize * sizeof(void *));
		if (stack->buf == NULL) {
			free(stack);
			return NULL;
		}
	}
	return stack;
}

void BOMStackFree(BOMStackRef stk) {
	struct __BOMStack *stack = (struct __BOMStack *)stk;
	
	free(stack->buf);
	free(stack);
}

void BOMStackPush(BOMStackRef stk, void *r14) {
	struct __BOMStack *stack = (struct __BOMStack *)stk;
	
	void **buffer = NULL;
	if (stack->count + 1 < stack->maxSize) {
		buffer = stack->buf;
	} else {
		stack->maxSize *= 2;
		buffer = realloc(stack->buf, stack->maxSize * sizeof(void *));
	}
	buffer[stack->count++] = r14;
	stack->buf = buffer;
}

void *BOMStackPop(BOMStackRef stk) {
	struct __BOMStack *stack = (struct __BOMStack *)stk;
	
	if (stack != NULL && stack->count > 0) {
		return stack->buf[stack->count--];
	}
	return NULL;
}

bool BOMStackIsEmpty(BOMStackRef stack) {
	return stack->count <= 0;
}

int32_t BOMStackCount(BOMStackRef stack) {
	if (stack != NULL) {
		return stack->count;
	}
	return 0;
}

