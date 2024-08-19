#ifndef _QNJ_MEMCPY_HPP_
#define _QNJ_MEMCPY_HPP_
#include "../qnj_config.h"
#include "qnj_alloc.hpp"

void* qnj_memcpy(void* qnj_destination_ptr, void* qnj_source_ptr, size_t qnj_size_sourceptr)
{
    if (qnj_destination_ptr == nullptr) 
    {
        std::cout << "Invalid destination of a pointer in qnj_memcpy." << std::endl;
        return nullptr;
    }
    else if (qnj_source_ptr == nullptr)
    {
        std::cout << "Invalid source of a pointer in qnj_memcpy." << std::endl;
        return nullptr;
    }
    else if (qnj_size_sourceptr == 0)
    {
        std::cout << "Invalid size amount of the source pointer in qnj_memcpy" << std::endl;
        return nullptr;
    } 

    std::memcpy(qnj_destination_ptr, qnj_source_ptr, qnj_size_sourceptr);
    return qnj_destination_ptr;
}

#endif