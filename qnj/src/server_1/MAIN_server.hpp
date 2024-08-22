#ifndef MAIN_SERVER_HPP
#define MAIN_SERVER_HPP

#include "../qnj_config.h"
#include "../memory/qnj_alloc.hpp"

int QNJ_Main_server_socket;

void set_socket_options(int socket_fd) {
    int reuseaddr = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) == -1) {
        std::cerr << "[ERR_SETTING_SOCKET_OPTIONS]" << "\n";
        perror("");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

void set_nonblocking(int socket_fd) {
    int flags = fcntl(socket_fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "[ERR_GETTING_SOCKET_FLAGS]" << "\n";
        perror("");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "[ERR_SETTING_NONBLOCKING]" << "\n";
        perror("");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

void SERVER_MAIN_QNJ()
{
    QNJ_Main_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (QNJ_Main_server_socket == -1)
    {
        std::cout << "[ERR_MAKING_SERVER_SOCKET]" << "\n";
        perror("");
        exit(EXIT_FAILURE);
    }

    set_socket_options(QNJ_Main_server_socket);
    set_nonblocking(QNJ_Main_server_socket);
}

void BIND_SERVER_QNJ(const std::string& address, int port)
{
    struct sockaddr_in MAIN_SERVER_ADDRESS;
    std::memset(&MAIN_SERVER_ADDRESS, 0, sizeof(MAIN_SERVER_ADDRESS));
    MAIN_SERVER_ADDRESS.sin_family = AF_INET;
    MAIN_SERVER_ADDRESS.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &MAIN_SERVER_ADDRESS.sin_addr);

    int bind_result = bind(QNJ_Main_server_socket, (struct sockaddr*)&MAIN_SERVER_ADDRESS, sizeof(MAIN_SERVER_ADDRESS));

    if (bind_result == -1)
    {
        std::cout << "[ERR_BINDING_MAIN_SOCKET]" << "\n";
        perror("");
        close(QNJ_Main_server_socket);
        exit(EXIT_FAILURE);
    }
}

void LISTEN_SERVER_QNJ()
{
    int listen_result = listen(QNJ_Main_server_socket, 5);
    if (listen_result == -1)
    {
        std::cout << "[ERR_LISTENING_MAIN_SOCKET]" << "\n";
        perror("");
        close(QNJ_Main_server_socket);
        exit(EXIT_FAILURE);
    }
}

#endif