#include "../qnj_config.h"
#include "../server_2/TCP_handle_client.hpp"

void extract_payload_file(const std::string& filename) 
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    char buffer[1024];
    while (file) 
    {
        file.read(buffer, sizeof(buffer));
        send(TCP_CLIENT_SOCKET, buffer, file.gcount(), 0);
    }

    file.close();
}