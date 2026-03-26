#ifndef GATOR_ALLOCATOR
#define GATOR_ALLOCATOR

#include <stddef.h>

#define GATOR_SUCCESS 0
#define GATOR_NULLPTR 1


void* gator_allocate(size_t bytes);
int gator_free(void* ptr);

#endif