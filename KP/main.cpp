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
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MKC_alloc.free(MKC_blocks[i]);
    }
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time of free MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;


//--------

    std::vector<void*> list_blocks2;
    std::vector<void*> MKC_blocks2;

    list_memory = sbrk(10000 * page_size * 100); 
    MKC_memory = sbrk(10000 * page_size * 100);

    FBLAllocator list_alloc2(list_memory, 10000 * page_size);
    MCKAllocator MKC_alloc2(MKC_memory, 1000 * page_size);
    std::cout << "Block allocation rate of 1000 bytes" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = list_alloc2.alloc(1000);
        list_blocks2.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = MKC_alloc2.alloc(1000);
        MKC_blocks2.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    std::cout << "Block free rate" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != list_blocks.size(); ++i) {
        list_alloc2.free(list_blocks2[i]);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MKC_alloc2.free(MKC_blocks2[i]);
    }
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time of free MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

//----------------------------

    std::vector<void*> list_blocks3;
    std::vector<void*> MKC_blocks3;

    list_memory = sbrk(10000 * page_size * 100); 
    MKC_memory = sbrk(10000 * page_size * 100);

    FBLAllocator list_alloc3(list_memory, 10000 * page_size);
    MCKAllocator MKC_alloc3(MKC_memory, 1000 * page_size);
    std::cout << "Block allocation rate of 3000 bytes" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = list_alloc3.alloc(3000);
        list_blocks3.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 100000; ++i) {
        void* block = MKC_alloc3.alloc(3000);
        MKC_blocks3.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    std::cout << "Block free rate" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != list_blocks.size(); ++i) {
        list_alloc3.free(list_blocks3[i]);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MKC_alloc3.free(MKC_blocks3[i]);
    }
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time of free MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;
//-----------------------------------------------------
    std::vector<void*> list_blocks4;
    std::vector<void*> MKC_blocks4;

    list_memory = sbrk(10000 * page_size * 100); 
    MKC_memory = sbrk(10000 * page_size * 100);

    FBLAllocator list_alloc4(list_memory, 10000 * page_size);
    MCKAllocator MKC_alloc4(MKC_memory, 10000 * page_size);
    std::cout << "Block allocation rate of 1000 bytes" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 10000000; ++i) {
        void* block = list_alloc4.alloc(200);
        list_blocks4.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != 10000000; ++i) {
        void* block = MKC_alloc4.alloc(200);
        MKC_blocks4.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    std::cout << "Block free rate" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != list_blocks.size(); ++i) {
        list_alloc4.free(list_blocks4[i]);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free FBLAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MKC_alloc4.free(MKC_blocks4[i]);
    }
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time of free MCKAllocator: " << 
                  std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << 
                  " milliseconds" << std::endl;

}