//
//  Bombe.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_PUBLIC__
#define __BOMBE_PUBLIC__

#ifdef __APPLE__
#include <Availability.h>
#include <TargetConditionals.h>
#endif
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#endif

/*
 * +-------------------------------------------------+
 * |                       BOM                       |
 * +-------------------------------------------------+
 * |                                                 |
 * |                      HEADER                     |
 * |                      ------                     |
 * |                                                 |
 * | 8  magic                    - 'BOMStore'        |
 * | 32 version                  -  1                |
 * | 32 ?                        - "73"              |
 * | 32 index offset             -                   |
 * | 32 index length             -                   |
 * | 32 table of contents offset -                   |
 * | 32 table of contents size   -                   |
 * |                                                 |
 * +-------------------------------------------------+
 * |                      Index                      |
 * +-------------------------------------------------+
 * |                     Block 1                     |
 * |                                                 |
 * | 32 index                                        |
 * | 8  name length                                  |
 * | ?  name                                         |
 * +-------------------------------------------------+
 * |                     Block 2                     |
 * +-------------------------------------------------+
 * |                       ...                       |
 * +-------------------------------------------------+
 * |                     Block n                     |
 * +-------------------------------------------------+
 */
