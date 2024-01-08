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


struct Page {
    Page* _next;
    bool _is_large;
    size_t _block_size;
};

class MCKAllocator final{
  private:
    void* _memory;
    Page* _free_pages_list;
    size_t _memory_size;
    size_t _page_size;

  public:
    MCKAllocator() = delete;
    MCKAllocator(void_pointer, size_type);

    virtual ~MCKAllocator();

    void_pointer alloc(size_type);
    void free(void_pointer);
};