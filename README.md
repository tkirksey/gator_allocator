# Gator Allocator
This project is my attempt at making a basic allocator.

## Documentation

---

#### `void *gator_allocate(size_t bytes)`

<ins>Description:</ins>

Returns a void pointer to the requested size of bytes

<ins>Parameters:</ins>

`size_t bytes` -> the number of bytes to allocate

<ins>Returns:</ins>

`void *` -> a pointer to the requested memory or NULL if failed to allocate memory

---

#### `int gator_free(void *ptr)`

<ins>Description:</ins>

Frees the allocated memory from the pointer and sets it to NULL
    
<ins>Parameters:</ins>

`void *ptr` -> the pointer to the memory to be freed

<ins>Returns:</ins>

`int` -> Either a 0 for success or an error code

---

### Error Code Lookup Table

|Error Code|Code Name|Meaning|
|:---|:---|:---|
|0|SUCCESS|The allocation was freed with no errors|
|1|NULLPTR|A NULL pointer was passed in as a parameter|

