#ifndef _QNJ_MEMORY_POOL_HPP_
#define _QNJ_MEMORY_POOL_HPP_
#include "qnj_memory_pool.h"
#include "../qnj_config.h"
#include "./qnj_alloc.hpp"

qnj_pool_t* qnj_create_pool(size_t size)
{
    qnj_pool_t *p = static_cast<qnj_pool_t*>(qnj_memalign(QNJ_POOL_ALIGNMENT, size));
    if (!p) {
        return nullptr;
    }

    p->d.last = reinterpret_cast<uint8_t*>(p) + sizeof(qnj_pool_t);
    p->d.end = reinterpret_cast<uint8_t*>(p) + size;
    p->d.next = nullptr;
    p->d.failed = 0;

    size -= sizeof(qnj_pool_t);
    p->max = (size < QNJ_MAX_ALLOC_FROM_POOL) ? size : QNJ_MAX_ALLOC_FROM_POOL; // max small pool amount is 1320 above is large

    p->current = p;
    p->chain = nullptr;
    p->large = nullptr;
    p->cleanup = nullptr;

    return p;
}

// Destroy a memory pool
void qnj_destroy_pool(qnj_pool_t *pool)
{
    qnj_pool_t *p, *n;
    qnj_pool_large_t *l;
    qnj_pool_cleanup_t *c;

    // Run cleanup handlers
    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            c->handler(c->data);
        }
    }

    // Free large allocations
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            qnj_free(l->alloc);
        }
    }

    // Free all memory pools
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        qnj_free(p);

        if (n == nullptr) {
            break;
        }
    }
}

// Reset a memory pool
void qnj_reset_pool(qnj_pool_t *pool)
{
    qnj_pool_t *p;
    qnj_pool_large_t *l;

    // Free large allocations
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            qnj_free(l->alloc);
        }
    }

    // Reset pool blocks
    for (p = pool; p; p = p->d.next) {
        p->d.last = reinterpret_cast<uint8_t*>(p) + sizeof(qnj_pool_t);
        p->d.failed = 0;
    }

    // Reset the pool state
    pool->current = pool;
    pool->chain = nullptr;
    pool->large = nullptr;
}

// Allocate from the pool
void* qnj_palloc(qnj_pool_t *pool, std::size_t size)
{
    if (size <= pool->max) {
        std::cout << "Allocating small pool amount" << std::endl;
        return qnj_palloc_small(pool, size, 1);
    }

    std::cout << "Allocating large pool amount" << std::endl;
    return qnj_palloc_large(pool, size);
}

// Allocate small memory blocks
static inline void* qnj_palloc_small(qnj_pool_t *pool, std::size_t size, int align)
{
    uint8_t *m;
    qnj_pool_t *p;

    p = pool->current;

    do {
        m = p->d.last;

        if (align) {
            m = reinterpret_cast<uint8_t*>((reinterpret_cast<std::uintptr_t>(m) + (QNJ_POOL_ALIGNMENT - 1)) & ~(QNJ_POOL_ALIGNMENT - 1));
        }

        if (static_cast<std::size_t>(p->d.end - m) >= size) {
            p->d.last = m + size;
            return m;
        }

        p = p->d.next;

    } while (p);

    return qnj_palloc_block(pool, size);
}

// Allocate a block of memory
static void* qnj_palloc_block(qnj_pool_t *pool, std::size_t size)
{
    uint8_t *m;
    std::size_t psize;
    qnj_pool_t *p, *new_block;

    psize = static_cast<std::size_t>(pool->d.end - reinterpret_cast<uint8_t*>(pool));

    m = reinterpret_cast<uint8_t*>(qnj_alloc(psize));
    if (m == nullptr) {
        return nullptr;  // Allocation failed
    }

    new_block = reinterpret_cast<qnj_pool_t*>(m);

    new_block->d.end = m + psize;
    new_block->d.next = nullptr;
    new_block->d.failed = 0;

    m += sizeof(qnj_pool_t);  // Adjust size here
    m = reinterpret_cast<uint8_t*>((reinterpret_cast<std::uintptr_t>(m) + (QNJ_POOL_ALIGNMENT - 1)) & ~(QNJ_POOL_ALIGNMENT - 1));
    new_block->d.last = m + size;

    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            pool->current = p->d.next;
        }
    }

    p->d.next = new_block;

    return m;
}

// Allocate large memory blocks
static void* qnj_palloc_large(qnj_pool_t *pool, std::size_t size)
{
    void *p;
    std::size_t n;
    qnj_pool_large_t *large;

    // Allocate memory for the large block
    p = qnj_alloc(size);
    if (p == nullptr) {
        return nullptr;  // Allocation failed
    }

    n = 0;

    // Check existing large allocations to find an empty slot
    for (large = pool->large; large; large = large->next) {
        if (large->alloc == nullptr) {
            large->alloc = p;
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    // Allocate a new large block list item if necessary
    large = static_cast<qnj_pool_large_t*>(qnj_palloc_small(pool, sizeof(qnj_pool_large_t), 1));
    if (large == nullptr) {
        qnj_free(p);
        return nullptr;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}

void* qnj_pmemalign(qnj_pool_t *pool, std::size_t size, std::size_t alignment)
{
    void *p;
    qnj_pool_large_t *large;

    p = qnj_memalign(alignment, size);
    if (p == nullptr) {
        return nullptr;
    }

    large = static_cast<qnj_pool_large_t*>(qnj_palloc_small(pool, sizeof(qnj_pool_large_t), 1));
    if (large == nullptr) {
        qnj_free(p);
        return nullptr;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}

qnj_int_t qnj_pfree(qnj_pool_t *pool, void *p)
{
    qnj_pool_large_t *l;

    for (l = pool->large; l; l = l->next) {
        if (p == l->alloc) {
            qnj_free(l->alloc);
            l->alloc = nullptr;

            return QNJ_OK;
        }
    }

    return QNJ_DECLINED;
}

void* qnj_pcalloc(qnj_pool_t *pool, std::size_t size)
{
    void *p;

    p = qnj_palloc(pool, size);
    if (p) {
        qnj_memzero(p, size);
    }

    return p;
}

qnj_pool_cleanup_t* qnj_pool_cleanup_add(qnj_pool_t *p, std::size_t size)
{
    qnj_pool_cleanup_t *c;

    c = static_cast<qnj_pool_cleanup_t*>(qnj_palloc(p, sizeof(qnj_pool_cleanup_t) + size));
    if (c == nullptr) {
        return nullptr;
    }

    c->handler = nullptr;
    c->data = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(c) + sizeof(qnj_pool_cleanup_t));
    c->next = p->cleanup;
    p->cleanup = c;

    return c;
}

#endif