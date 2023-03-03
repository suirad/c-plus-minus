#if defined(__linux__) || defined(__APPLE__)
typedef unsigned long size_t;
#else
typedef unsigned long long size_t;
#endif
typedef unsigned char uint8_t;

// Define the size of the memory pool
#define POOL_SIZE 1024

// Define a block of memory that will act as our pool
uint8_t pool[POOL_SIZE];

// Define a struct to represent a block of memory
struct block_t {
  size_t size;
  bool is_free;
  block_t *next;
};

// Define a pointer to the beginning of the memory pool
block_t *head = (block_t *)pool;

// Define a class for the custom allocator
class CustomAllocator {
public:
  void *allocate(size_t size) {
    block_t *curr_block = head;
    [[maybe_unused]] block_t *prev_block = nullptr;
    while (curr_block) {
      if (curr_block->is_free && curr_block->size >= size) {
        if (curr_block->size >= size + sizeof(block_t) + 1) {
          split_block(curr_block, size);
        }
        curr_block->is_free = false;
        return (void *)(curr_block + 1);
      }
      prev_block = curr_block;
      curr_block = curr_block->next;
    }
    return nullptr;
  }

  void deallocate(void *ptr) {
    if (!ptr) {
      return;
    }
    block_t *curr_block = (block_t *)ptr - 1;
    curr_block->is_free = true;
    merge_blocks();
  }

  // Define a function to initialize the memory pool
  void initialize_pool() {
    head->size = POOL_SIZE - sizeof(block_t);
    head->is_free = true;
    head->next = nullptr;
  }

private:
  // Define a function to split a block into two smaller blocks
  void split_block(block_t *block, size_t size) {
    block_t *new_block = (block_t *)((uint8_t *)block + sizeof(block_t) + size);
    new_block->size = block->size - size - sizeof(block_t);
    new_block->is_free = true;
    new_block->next = block->next;
    block->size = size;
    block->is_free = false;
    block->next = new_block;
  }

  // Define a function to merge adjacent free blocks
  void merge_blocks() {
    block_t *curr_block = head;
    while (curr_block) {
      if (curr_block->is_free && curr_block->next &&
          curr_block->next->is_free) {
        curr_block->size += sizeof(block_t) + curr_block->next->size;
        curr_block->next = curr_block->next->next;
      }
      curr_block = curr_block->next;
    }
  }
};