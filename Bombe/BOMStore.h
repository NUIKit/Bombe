//
//  BOMStore.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//


/*
 * +-------------------------------------+
 * |                                     |
 * |               HEADER                |
 * |               ------                |
 * |                                     |
 * | 8  magic                            |
 * | 32 version                          |
 * | 32 block count                      |
 * | 32 index offset                     |
 * | 32 index length                     |
 * | 32 table of contents offset         |
 * | 32 table of contents size           |
 * |                                     |
 * +-------------------------------------+
 *
 * Fig. 1.   The BOM header begins with a magic number, spelling 'BOMStore', followed by a version
 *        number.  After that we are given the number of blocks present in the index, the offset
 *        at which to find such blocks, and the total length of the blocks section.  Each block is
 *        a pointer into the BOM file to some chunk of data for an asset.  After that comes the
 *        Table of Contents offset and size.  Entries in the table of contents are blocks, but they
 *        also include a name that can be looked up.  
 */


#ifndef __BOMBE_STORE__
#define __BOMBE_STORE__

#include <Bombe/BOMDefines.h>

#include <stdbool.h>
#include <stdlib.h>

/// The type of references to immutable BOM Stores.
typedef const struct __BOMStore * BOMStoreRef;

/// The type of references to mutable BOM Stores.
typedef struct __BOMStore * BOMMutableStoreRef;

typedef struct __BOMBlock {
	uint32_t index;
	uint32_t size;
} BOMBlock;

/// Creates an immutable store from the BOM file at a given path.
BOMBE_EXPORT
BOMStoreRef BOMStoreCreateWithPath(const char *path);

/// Frees a store and its associated resources.
BOMBE_EXPORT
void BOMStoreFree(BOMStoreRef store);

/// Gets a block entry in the table of contents with the given name.
BOMBE_EXPORT
bool BOMStoreGetBlockWithName(BOMStoreRef sto, const char *name, BOMBlock *outBlock);

/// Returns the size of a given block in the store.
///
/// If the block does not exist, or it resides at an invalid index, the result will be 0.
BOMBE_EXPORT
uint32_t BOMStoreGetBlockSize(BOMStoreRef sto, BOMBlock block);

/// Returns the data associated with a given block.
///
/// It is the responsibility of the caller to release the pointer given by this function.
BOMBE_EXPORT
void *BOMStoreCopyBlockData(BOMStoreRef sto, BOMBlock block);


/// Creates a mutable store from the BOM file at a given path.
BOMBE_EXPORT
BOMMutableStoreRef BOMStoreCreateMutableWithPath(const char *path);

/// Creates and adds a new empty block to the BOM store.  The result of this function is the Block 
/// ID of the added block.
BOMBE_EXPORT
uint32_t BOMStoreCreateNewBlock(BOMMutableStoreRef sto);

#endif
