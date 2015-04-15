//
//  Defines.h
//  Bombe
//
//  Created by Robert Widmann on 2/6/15.
//  Copyright (c) 2015 CodaFi. All rights reserved.
//

#ifndef __BOMBE_DEFINES__
#define __BOMBE_DEFINES__

#if defined(__cplusplus)
	#define BOMBE_EXPORT extern "C" extern __declspec(dllexport)
#elif __GNUC__
	#define BOMBE_EXPORT extern __attribute__((visibility("default")))
#else
	#define BOMBE_EXPORT extern
#endif

#if __GNUC__
	#define BOMBE_INLINE static __inline__
#else
	#define BOMBE_INLINE static inline
#endif

#if __GNUC__
	#define BOMBE_EXPECT(x, v) __builtin_expect((x), (v))
#else
	#define BOMBE_EXPECT(x, v) (x)
#endif

#define BOMAssert(e, MSG) \
	do { \
		typeof(e) _e = ((typeof(e))__builtin_expect((long)(e), ~0l)); \
		if (!_e) { \
			abort(); \
		} \
	} while (0)

#endif
