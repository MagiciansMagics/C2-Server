#include "../qnj_config.h"
#include "../server_2/TCP_handle_client.hpp"
void send_client_tcp_data(const char* buffer, std::streamsize size, int target_socket)
{
    // Ensure the buffer is valid and size is positive
    if (buffer && size > 0) {
        ssize_t sent_bytes = send(target_socket, buffer, size, 0);
        if (sent_bytes == -1) {
            std::cerr << "Error sending data to client" << std::endl;
        }
    }
}

void extract_payload_file(const std::string& filename, int target_socket) 
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)))
    {
        send_client_tcp_data(buffer, file.gcount(), target_socket);
    }

    // Handle any remaining bytes that were not sent yet
    if (file.gcount() > 0) 
    {
        send_client_tcp_data(buffer, file.gcount(), target_socket);
    }

    file.close();
}