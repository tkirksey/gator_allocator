// I know the irony of using malloc(). Don't tell me -tk

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "gator_allocator.h"

// 64-bit chunks (double words)
#define GATOR_CHUNK_SIZE 8

typedef struct _ALLOCATION_ENTRY {
    void* start;
    size_t chunks;
    void* next;
} ALLOCATION_ENTRY;

typedef struct _GATOR_META {
    void *memory_start;
    size_t total_bytes;
    ALLOCATION_ENTRY *free_table;
} GATOR_META ;

GATOR_META gator_metadata = {
    .memory_start = NULL,
    .total_bytes = 0,
    .free_table = NULL
};

int init_gator_alloc(size_t requestedBytes);

#define GATOR_MMAP_FAIL 1
#define GATOR_MALLOC_FAIL 2

void* gator_allocate(size_t bytes) {

    // nothing to allocate
    if(bytes == 0){
        return NULL;
    }

    size_t chunks = bytes / 8;

    // chuckatize your bytes!!
    if(bytes % GATOR_CHUNK_SIZE != 0){
        bytes += GATOR_CHUNK_SIZE - (bytes % GATOR_CHUNK_SIZE);
        chunks = bytes / 8;
    }

    if(gator_metadata.memory_start == NULL){
        // initialize allocator
        int err = init_gator_alloc(bytes);

        if(err == GATOR_MMAP_FAIL || err == GATOR_MALLOC_FAIL){
            return NULL;
        }
    }

    // TODO: allocate memory from page;

    return NULL;

}

int gator_free(void* ptr) {

    if(ptr == NULL){
        return GATOR_NULLPTR;
    }

    // if pointer was not allocated by the allocator
    if(ptr < gator_metadata.memory_start || ptr > ((char *)(gator_metadata.memory_start) + gator_metadata.total_bytes)){
        return GATOR_NOTMYPTR;
    }

    // TODO: free memory from page;

    ptr = NULL;
    return GATOR_SUCCESS;

}

int init_gator_alloc(size_t requestedBytes){

    const size_t default_total_bytes = 16 * 1024; // 16kb
    
    void *addr = NULL;
    bool isDefaultSize = true;

    if(requestedBytes > default_total_bytes){

        void *addr = mmap(NULL, requestedBytes, PROT_READ | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        isDefaultSize = false;

    } else {

        void *addr = mmap(NULL, default_total_bytes, PROT_READ | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        isDefaultSize = true;

    }

    if(addr == MAP_FAILED){
        return GATOR_MMAP_FAIL;
    }

    gator_metadata.memory_start = addr;
    gator_metadata.total_bytes = isDefaultSize ? default_total_bytes : requestedBytes;

    ALLOCATION_ENTRY *base_entry = malloc(sizeof(ALLOCATION_ENTRY));
    ALLOCATION_ENTRY *entry = malloc(sizeof(ALLOCATION_ENTRY));
    if(entry == NULL || base_entry == NULL) {
        return GATOR_MALLOC_FAIL;
    }

    base_entry->start = gator_metadata.memory_start;
    base_entry->chunks = 0;
    base_entry->next = entry;

    entry->start = gator_metadata.memory_start;
    entry->chunks = gator_metadata.total_bytes % 8;
    entry->next = NULL;

    gator_metadata.free_table = entry;

    return 0;

}