#ifndef SMART_HANDLE_CLIENTS_HPP
#define SMART_HANDLE_CLIENTS_HPP
#include "../qnj_config.h"
#include "../networking/Parse_stuff/parse_tcp_clients_send_data.hpp"

std::string return_client_data(char* buffer, int bytes_recv)
{
    try 
    {
        std::string received_data(buffer, bytes_recv);
        std::string ip, os, osRelease, architecture;
        parseClientData(received_data, ip, os, osRelease, architecture);
        std::string full_client_data = ip + " " + os + " " + osRelease + " " + architecture;
        return full_client_data;
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error in tcp smart handle: " << e.what() << "\n";
        return "none";
    }
}

#endif