#ifndef QNJ_MEMORY_POOL_HPP
#define QNJ_MEMORY_POOL_HPP

#include "../qnj_config.h"

// Define constants
#define QNJ_POOL_ALIGNMENT 16
#define QNJ_MAX_ALLOC_FROM_POOL 4096

// Define types and constants if they are not defined elsewhere
using qnj_int_t = int;
using qnj_fd_t = int; // Assuming file descriptors are integers
using qnj_err_t = int;
constexpr int QNJ_FILE_ERROR = -1;
constexpr int QNJ_ENOENT = ENOENT; // Standard ENOENT value
constexpr int QNJ_OK = 0;
constexpr int QNJ_DECLINED = -1;

// Define the qnj_log_t structure
struct qnj_log_t {
    void error(const char* message) {
        std::fprintf(stderr, "Error: %s\n", message);
    }
};

// Define the qnj_pool_cleanup_t structure
struct qnj_pool_cleanup_t {
    void (*handler)(void *data);
    void *data;
    qnj_pool_cleanup_t *next;
};

// Define the qnj_pool_large_t structure
struct qnj_pool_large_t {
    void *alloc;
    qnj_pool_large_t *next;
};

// Define the qnj_pool_t structure
struct qnj_pool_s {
    struct {
        uint8_t     *last;
        uint8_t     *end;
        qnj_pool_s  *next;
        unsigned     failed : 1;
    } d;

    std::size_t    max;
    qnj_pool_s    *current;
    void          *chain;
    qnj_pool_large_t *large;
    qnj_pool_cleanup_t *cleanup;
    qnj_log_t     *log;
};

typedef qnj_pool_s qnj_pool_t;

// Function declarations
qnj_pool_t *qnj_create_pool(size_t size);
void qnj_destroy_pool(qnj_pool_t *pool);
void qnj_reset_pool(qnj_pool_t *pool);
static void* qnj_palloc_block(qnj_pool_t *pool, std::size_t size);
static inline void* qnj_palloc_small(qnj_pool_t *pool, std::size_t size, int align);
static void* qnj_palloc_large(qnj_pool_t *pool, std::size_t size);
void* qnj_palloc(qnj_pool_t *pool, std::size_t size);

#endif