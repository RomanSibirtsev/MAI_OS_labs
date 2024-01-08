#include <chrono>
#include <cstdlib>
#include <vector>

#include "MCKAllocator.hpp"
#include "FBLAllocator.hpp"

size_t page_size = sysconf(_SC_PAGESIZE);

int main() {

    void* list_memory = sbrk(10000 * page_size * 100); 
    void* MKC_memory = sbrk(10000 * page_size * 100);

    FBLAllocator list_alloc(list_memory, 10000 * page_size);
    MCKAllocator MKC_alloc(MKC_memory, 1000 * page_size);
    std::vector<void*> list_blocks;
    std::vector<void*> MKC_blocks;

    std::cout << "Comparing FBLAllocator and MCKAllocator" << std::endl;

    std::cout << "Block allocation rate" << std::endl;
    auto start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = list_alloc.alloc(i % 1000 + 100);
        list_blocks.push_back(block);
    }
    auto end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = MKC_alloc.alloc(i % 1000 + 100);
        MKC_blocks.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    std::cout << "Block free rate" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != list_blocks.size(); ++i) {
        list_alloc.free(list_blocks[i]);
        if (i < 20) {
            std::cout << list_blocks[i] << std::endl;
        }
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MKC_alloc.free(MKC_blocks[i]);
        if (i < 20) {
            std::cout << MKC_blocks[i] << std::endl;
        }
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;
}