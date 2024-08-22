#ifndef _SAVE_TCP_CLIENT_CONNECTIONS_HPP_
#define _SAVE_TCP_CLIENT_CONNECTIONS_HPP_

#include "../qnj_config.h"

void save_client_connection_tcp(const std::string& connection_data)
{
    std::ofstream connection_file("/root/qnj-server/save_client_connection.log");

    connection_file << connection_data;
}

std::string return_client_connections_file()
{
    std::ifstream connection_file("/root/qnj-server/save_client_connection.log");
    std::string clients;

    while (std::getline(connection_file, clients))
    {
        return clients;
    }

    return "";
}

#endif