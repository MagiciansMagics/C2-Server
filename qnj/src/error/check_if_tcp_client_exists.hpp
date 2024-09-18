#include "../qnj_config.h"

bool check_tcp_client_existance(std::string id)
{
    int value;
    try 
    {
        value = std::stoi(id); // Convert the passed client ID to an integer
    } 
    catch (const std::invalid_argument& e) 
    {
        std::cerr << "Invalid argument: id is not a number" << std::endl;
        return false;
    } 
    catch (const std::out_of_range& e) 
    {
        std::cerr << "Out of range error: id is too large" << std::endl;
        return false;
    }

    int target_socket = QNJ_TCP_CLIENT_SOCKET[value];

    char buffer[2] = " ";
    ssize_t bytes_send = send(target_socket, buffer, strlen(buffer), 0);

    if (bytes_send == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            std::cout << "Socket not useable 1" << std::endl;
            return false;
        }
        else
        {
            std::cout << "Socket not useable 2" << std::endl;
            return false;
        }
    }
    return true;
}
