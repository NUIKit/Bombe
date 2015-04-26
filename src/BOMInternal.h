//
//  Internal.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_INTERNAL__
#define __BOMBE_INTERNAL__

#include <config/config.h>

#if HAVE_LIBKERN_OSCROSSENDIAN_H
#include <libkern/OSCrossEndian.h>
#endif /* HAVE_LIBKERN_OSCROSSENDIAN_H */

#if HAVE_LIBKERN_OSATOMIC_H
#include <libkern/OSAtomic.h>
#endif /* HAVE_LIBKERN_OSATOMIC_H */

#if HAVE_MACH
#include <mach/boolean.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <mach/vm_map.h>
#elif HAVE_VM_VM_H && HAVE_VM_VM_MAP_H && HAVE_VM_VM_OBJECT_H
#include <vm/vm.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#elif HAVE_SYS_MMAN_H && HAVE_UNISTD_H
#include <unistd.h>
#include <sys/mman.h>
#define vm_size_t		size_t	/* No VM in sight. */
#define vm_address_t	size_t
#define KERN_SUCCESS	0		/* But a guy can dream, can't he? */
#else
#error Current target does not support mmap
#endif /* HAVE_MACH */

#if HAVE_MALLOC_MALLOC_H
#include <malloc/malloc.h>
#endif /* HAVE_MALLOC_MALLOC_H */

#include <sys/stat.h>

#if !TARGET_OS_WIN32 
#include <sys/mman.h>
#else
#include "sys_queue.h"
#endif

#include <assert.h>
#include <errno.h>

#if HAVE_FCNTL_H
#include <fcntl.h>
#endif /* HAVE_FCNTL_H */

#include <limits.h>
#include <search.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

/* For Linux where PAGE_SIZE is a kernel call. */
#ifndef PAGE_SIZE
#define PAGE_SIZE getpagesize()
#define vm_page_size getpagesize()
#endif

#endif
