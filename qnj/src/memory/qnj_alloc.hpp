#ifndef _QNJ_MALLOC_HPP_
#define _QNJ_MALLOC_HPP_
#include "../qnj_config.h"
#include "./qnj_alloc.h"

void* qnj_alloc(size_t qnj_memt_allocate)
{
    void* qnj_allocated_mem = std::malloc(qnj_memt_allocate);

    if (qnj_allocated_mem == nullptr || qnj_allocated_mem == NULL)
    {
        std::cout << "qnj_malloc failed to allocated a null pointer" << std::endl;
        return nullptr;
    }

    return qnj_allocated_mem;
}

void* qnj_calloc(size_t size)
{
    void  *p;

    p = qnj_alloc(size);

    if (p) {
        qnj_memzero(p, size);
    }

    return p;
}

void qnj_memzero(void* p, size_t size)
{
    if (p == NULL || p == nullptr)
    {
        std::cout << "Pointer is null in memzero" << std::endl;
    }

    std::memset(p, 0, size);
}

void* qnj_memalign(std::size_t alignment, std::size_t size)
{
    if ((alignment & (alignment - 1)) != 0 || alignment == 0) {
        return nullptr;
    }

    void* ptr = std::aligned_alloc(alignment, size);
    if (!ptr) {
        std::cout << "Memory allocation failed" << std::endl;
    }

    return ptr;
}

void qnj_free(void* qnj_allocated_mem)
{
    if (qnj_allocated_mem == nullptr)
    {
        std::cout << "Attemping to free a null pointer. Failed" << std::endl;
    }
    else if (qnj_allocated_mem != nullptr)
    {
        std::free(qnj_allocated_mem);
    }
}

#endif