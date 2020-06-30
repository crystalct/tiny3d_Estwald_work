#include "rsxtiny.h"

static s8 initialized = 0;
gcmConfiguration config;
void *heap_pointer;

extern void debugPrintf(const char* fmt, ...);

// Really dumb allocater, It will do until we start dealing with textures and vertex buffers.
void *rsxtiny_MemAlign(s32 alignment, s32 size) {
	if (!initialized || alignment==-1 ) {
		gcmGetConfiguration(&config);
		initialized = 1;
        #ifdef OLD_TINY3D
		heap_pointer = (void *)(u64)config.localAddress;
        #else
        heap_pointer = (void *) config.localAddress;
        #endif

       if(alignment==-1) return NULL;
	}
	debugPrintf("config.localAddress: %p\n",config.localAddress);
	void *pointer = heap_pointer;
	pointer = (void *)((((u64) pointer) + (alignment-1)) & (-alignment)); // Align
    #ifdef OLD_TINY3D
	if ((u64) pointer + size > config.localAddress + config.localSize) // Out of memory?
		return NULL;
    #else
    if ((u64) pointer + size > ((u64)(void *) config.localAddress) + config.localSize) // Out of memory?
		return NULL;
    #endif
	heap_pointer = (void *)((u64) pointer + size);
	debugPrintf("heap_pointer: %p\n",heap_pointer);
	debugPrintf("pointer: %p\n",pointer);
	return pointer;
}

void *rsxtiny_Mem(s32 size) {
	return rsxtiny_MemAlign(64, size);
}


