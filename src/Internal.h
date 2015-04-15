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
#endif
#if HAVE_LIBKERN_OSATOMIC_H
#include <libkern/OSAtomic.h>
#endif
#if HAVE_MACH
#include <mach/boolean.h>
#include <mach/clock_types.h>
#include <mach/clock.h>
#include <mach/exception.h>
#include <mach/mach.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/mach_interface.h>
#include <mach/mach_time.h>
#include <mach/mach_traps.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/host_special_ports.h>
#include <mach/host_info.h>
#include <mach/notify.h>
#include <mach/mach_vm.h>
#include <mach/vm_map.h>
#endif /* HAVE_MACH */
#if HAVE_MALLOC_MALLOC_H
#include <malloc/malloc.h>
#endif

#include <sys/stat.h>

#if !TARGET_OS_WIN32 
#include <sys/event.h>
#include <sys/mount.h>
#include <sys/queue.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <netinet/in.h>
#else
#include "sys_queue.h"
#endif

#include <assert.h>
#include <errno.h>
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif
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
#endif

#endif
