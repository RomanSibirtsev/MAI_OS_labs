#include "FBLAllocator.hpp"

FBLAllocator::FBLAllocator(void_pointer real_memory, size_type memory_size)
{
    _free_blocks_list = reinterpret_cast<BlockHeader*>(real_memory + sizeof(FBLAllocator));
    _free_blocks_list->_size = memory_size - sizeof(FBLAllocator) - sizeof(BlockHeader);
    _free_blocks_list->_next = nullptr;
}

FBLAllocator::~FBLAllocator()
{
    BlockHeader* cur_block = this->_free_blocks_list;

    while (cur_block) {
        BlockHeader* to_delete = cur_block;
        cur_block = cur_block->_next;
        to_delete = nullptr;
    }

    this->_free_blocks_list = nullptr;
}

void_pointer FBLAllocator::alloc(size_type new_block_size)
{
    BlockHeader* prev_block = nullptr;
    BlockHeader* cur_block = this->_free_blocks_list;

    size_type adjusted_size = new_block_size + sizeof(BlockHeader);

    int diff = new_block_size * 100;

    while (cur_block) {
        if (cur_block->_size >= adjusted_size && cur_block->_size - adjusted_size < diff) {
            diff = cur_block->_size;
        }
        prev_block = cur_block;
        cur_block = cur_block->_next;
    }

    prev_block = nullptr;
    cur_block = this->_free_blocks_list;

    while (cur_block) {
        if (cur_block->_size >= adjusted_size) {
            if (cur_block->_size >= adjusted_size + sizeof(BlockHeader)) {
                BlockHeader* new_block = reinterpret_cast<BlockHeader*>(reinterpret_cast<int8_t*>(cur_block) + adjusted_size);

                new_block->_size = cur_block->_size - adjusted_size - sizeof(BlockHeader);
                new_block->_next = cur_block->_next;
                cur_block->_next = new_block;
                cur_block->_size = adjusted_size;
            }

            if (prev_block) {
                prev_block->_next = cur_block->_next;
            } else {
                this->_free_blocks_list = cur_block->_next;
            }

            return reinterpret_cast<int8_t*>(cur_block) + sizeof(BlockHeader);
        }

        prev_block = cur_block;
        cur_block = cur_block->_next;
    }

    return nullptr;
}

void FBLAllocator::free(void_pointer block)
{
    if (block == nullptr) return;

    BlockHeader* header = reinterpret_cast<BlockHeader*>(static_cast<int8_t*>(block) - sizeof(BlockHeader));
    header->_next = this->_free_blocks_list;
    this->_free_blocks_list = header;
}