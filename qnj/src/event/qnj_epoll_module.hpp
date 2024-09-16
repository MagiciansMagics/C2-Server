#ifndef _QNJ_EPOLL_MODULE_HPP_
#define _QNJ_EPOLL_MODULE_HPP_

#include "../qnj_config.h"

int qnj_epoll_create(int size)
{
    int p = epoll_create(size);
    if (p == -1) {
        perror("epoll_create failed");
        return -1;
    }
    return p;
}

int qnj_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    int p = epoll_ctl(epfd, op, fd, event);
    if (p == -1) {
        perror("epoll_ctl failed");
        return -1;
    }
    return p;
}

int qnj_epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
{
    int n = epoll_wait(epfd, events, maxevents, timeout);
    if (n == -1) {
        perror("epoll_wait failed");
        return -1;
    }
    return n;
}

#endif