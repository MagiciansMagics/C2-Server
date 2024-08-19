#ifndef MAIN_SERVER_HPP
#define MAIN_SERVER_HPP

#include "../qnj_config.h"
#include "../memory/qnj_alloc.hpp"

int QNJ_Main_server_socket;

void SERVER_MAIN_QNJ()
{
    QNJ_Main_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (QNJ_Main_server_socket == -1)
    {
        std::cout << "[ERR_MAKING_SERVER_SOCKET]" << "\n";
        perror("");
        exit(EXIT_FAILURE);
    }
}

void BIND_SERVER_QNJ(const std::string& address, int port)
{
    struct sockaddr_in MAIN_SERVER_ADDRESS;
    qnj_memzero(&MAIN_SERVER_ADDRESS, sizeof(MAIN_SERVER_ADDRESS));
    MAIN_SERVER_ADDRESS.sin_family = AF_INET;
    MAIN_SERVER_ADDRESS.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &MAIN_SERVER_ADDRESS.sin_addr);

    int bind_result = bind(QNJ_Main_server_socket, (struct sockaddr*)&MAIN_SERVER_ADDRESS, sizeof(MAIN_SERVER_ADDRESS));

    if (bind_result == -1)
    {
        std::cout << "[ERR_BINDING_MAIN_SOCKET]" << "\n";
        perror("");
        close(QNJ_Main_server_socket); // Close the server socket before exiting
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