#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP
#include "../qnj_config.h"

int QNJ_TCP_Main_server_socket, QNJ_TCP_Main_listen_socket, QNJ_TCP_Main_bind_socket;

void QNJ_TCP_MAIN_SOCKET()
{
    QNJ_TCP_Main_server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (QNJ_TCP_Main_server_socket == -1)
    {
        std::cout << "[ERR_MAKING_SERVER_SOCKET_TCP]" << "\n";
        perror("");
        exit(EXIT_FAILURE);
    }
}

void QNJ_TCP_BIND_SOCKET(const std::string& address, const int port)
{
    struct sockaddr_in QNJ_TCP_SERVER_ADDRESS;
    QNJ_TCP_SERVER_ADDRESS.sin_family = AF_INET;
    QNJ_TCP_SERVER_ADDRESS.sin_port = htons(port);
    QNJ_TCP_SERVER_ADDRESS.sin_addr.s_addr = inet_addr(address.c_str());

    QNJ_TCP_Main_bind_socket = bind(QNJ_TCP_Main_server_socket, (struct sockaddr*)&QNJ_TCP_SERVER_ADDRESS, sizeof(QNJ_TCP_SERVER_ADDRESS));

    if (QNJ_TCP_Main_bind_socket == -1)
    {
        std::cout << "[ERR_BINDING_MAIN_SOCKET_TCP]" << "\n";
        perror("");
        exit(EXIT_FAILURE);
    }
}

void QNJ_TCP_LISTEN_SOCKET()
{
    QNJ_TCP_Main_listen_socket = listen(QNJ_TCP_Main_server_socket, 5);

    if (QNJ_TCP_Main_listen_socket == -1)
    {
        std::cout << "[ERR_LISTENING_MAIN_SOCKET_TCP]" << "\n";
        perror("");
        exit(EXIT_FAILURE);
    }
}

#endif