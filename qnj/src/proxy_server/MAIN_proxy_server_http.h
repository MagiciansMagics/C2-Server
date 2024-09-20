#ifndef _MAIN_PROXY_SERVER_HTTP_H_
#define _MAIN_PROXY_SERVER_HTTP_H_

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "./MAIN_proxy_checker.h"

int qnj_http_server_socket, qnj_http_client_socket;
struct sockaddr_in server_address;

bool qnj_bind_server(int target_socket, const std::string address)
{
    if (inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        // Resolve the hostname, as it's not an IP address
        if ((he = gethostbyname(address.c_str())) == NULL)
        {
            // gethostbyname failed
            perror("gethostbyname");
            std::cout << "Failed to resolve hostname\n";
            return false;
        }

        // Cast the h_addr_list to in_addr, since h_addr_list also has the IP address in long format
        addr_list = (struct in_addr **)he->h_addr_list;

        for (int i = 0; addr_list[i] != NULL; i++)
        {
            server_address.sin_addr = *addr_list[i];
            std::cout << address << " resolved to " << inet_ntoa(*addr_list[i]) << std::endl;
            break;
        }
    }
    else
    {
        server_address.sin_addr.s_addr = inet_addr(address.c_str());
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(qnj_bind_proxy_server_port); // Adjust port number as needed

    if (bind(target_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        perror("Proxy server failed to bind");
        return false;
    }

    return true;
}

#endif