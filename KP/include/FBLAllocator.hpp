#pragma once

#include <exception>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

using void_pointer = void*;
using size_type = std::size_t;
using difference_type = std::ptrdiff_t;
using propagate_on_container_move_assignment = std::true_type;
using is_always_equal = std::true_type;

struct BlockHeader {
    size_t _size;
    BlockHeader* _next;
};

class FBLAllocator final{
  private:
    BlockHeader* _free_blocks_list;

  public:
    FBLAllocator() = delete;
    FBLAllocator(void_pointer, size_type);

    virtual ~FBLAllocator();

    void_pointer alloc(size_type);
    void free(void_pointer);
};