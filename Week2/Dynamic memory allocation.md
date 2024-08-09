### Dynamic Memory Functions

- **`malloc()`** 
  - **Description:** Allocates a block of memory and returns a pointer to the beginning of the block. The memory is uninitialized.
  - **Syntax:** `void* malloc(size_t size);`

- **`calloc()`** 
  - **Description:** Allocates a block of memory for an array of elements, initializes all bytes in the allocated storage to zero, and returns a pointer to the memory.
  - **Syntax:** `void* calloc(size_t num, size_t size);`

- **`realloc(void *p, size_t size)`**
  - **Description:** Changes the size of the memory block pointed to by `p` to `size` bytes. The contents up to the minimum of the old and new sizes are preserved. If the new size is larger, the additional memory will be uninitialized.
  - **Syntax:** `void* realloc(void* ptr, size_t size);`

- **`free()`** 
  - **Description:** Deallocates the memory previously allocated by a call to `malloc()`, `calloc()`, or `realloc()`. The behavior is undefined if the memory was not previously allocated by one of these functions.
  - **Syntax:** `void free(void* ptr);`
