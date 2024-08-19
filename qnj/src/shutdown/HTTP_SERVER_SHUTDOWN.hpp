#ifndef _HTTP_SERVER_SHUTDOWN_HPP_
#define _HTTP_SERVER_SHUTDOWN_HPP_
#include "../qnj_config.h"
#include "../server_1/MAIN_server.hpp"
#include "../server_2/TCP_server.hpp"
#include "../server_2/TCP_handle_client.hpp"

void forceful_shutdown()
{
    exit(0);
}

void terminate_http_server_session(int client_socket)
{   
    if (close(client_socket) == -1)
    {
        perror("[ERR_SHUTTING_CLIENT_SOCKET_HTTP]");
        forceful_shutdown();
    }
    
    if (close(QNJ_Main_server_socket) == -1)
    {
        perror("[ERR_SHUTTING_SERVER_SOCKET_HTTP]");
        forceful_shutdown();
    }
}

void terminate_tcp_server_session()
{
    if (close(TCP_CLIENT_SOCKET) == -1)
    {
        perror("[ERR_SHUTTING_CLIENT_SOCKET_TCP]");
        forceful_shutdown();
    }
    if (close(QNJ_TCP_Main_server_socket) == -1)
    {
        perror("[ERR_SHUTTING_SERVER_SOCKET_TCP]");
        forceful_shutdown();
    }
}

void shutdown_both_server(int client_socket)
{
    terminate_http_server_session(client_socket);
    terminate_tcp_server_session();
    forceful_shutdown();
}

#endif