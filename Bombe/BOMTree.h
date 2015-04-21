//
//  BOMTree.h
//  Bombe
//
//  Created by Robert Widmann on 2/7/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

/*
 * +-------------------------------------+
 * |                                     |
 * |                TREE                 |
 * |                ----                 |
 * |                                     |
 * | 8  magic                            |
 * | 32 version                          |
 * | ?            Root Node              |
 * |                  |                  |
 * |                 / \                 |
 * |                /   \                |
 * |            File     Node            |
 * |                       |             |
 * |                      / \            |
 * |                     /   \           |
 * |                 File     File       |
 * +-------------------------------------+
 *
 * Fig. 2.   A tree is a named block in the table of contents of a BOM file that points to a number
 *       of paths and files.  A tree is comprised of nodes that either point to file paths if they
 *       reside at a leaf, or point to another node if they sit at a branch.
 */

#ifndef __BOMBE_BOMTREE__
#define __BOMBE_BOMTREE__

#include <Bombe/BOMDefines.h>
#include <Bombe/BOMStore.h>

/// The type of BOM trees.
typedef const struct __BOMTree * BOMTreeRef;

/// Creates a new tree that loads a named entry in the table of contents in the given BOM store.
///
/// If the named block does not exist in the store, the result is NULL.
BOMBE_EXPORT
BOMTreeRef BOMTreeCreateTraversingPath(BOMStoreRef store, const char *name);

/// Releases a tree and its associated nodes and resources.
BOMBE_EXPORT
void BOMTreeFree(BOMTreeRef tree);

#endif
