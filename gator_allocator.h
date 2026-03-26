#ifndef GATOR_ALLOCATOR
#define GATOR_ALLOCATOR

#include <stddef.h>

void* gator_allocate(size_t bytes);
int gator_free(void* ptr);

#endif