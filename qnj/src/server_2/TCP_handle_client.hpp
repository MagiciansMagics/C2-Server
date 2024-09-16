#ifndef TCP_HANDLE_CLIENT_HPP
#define TCP_HANDLE_CLIENT_HPP
#include "../qnj_config.h"
#include "../json/save_tcp_database_json.hpp"
#include "./smart_handle_clients.hpp"
#include "./TCP_handle_client.h"
#include "../networking/utils/generate_random_string.hpp"
#include "../networking/utils/check_if_file_is_png.hpp"

std::string extract_client_vector_data()
{
    std::string result;
    for (const std::string& magic : client_id_array)
    {
        result += magic + "<br>";
    }

    return result;
}

void set_socket_nonblocking(int socket_fd) {
    int flags = fcntl(socket_fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "Error getting socket flags" << std::endl;
        return;
    }
    if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "Error setting socket to non-blocking" << std::endl;
    }
}

void update_client_id_array(const std::string& client_info, bool connected, const std::string& client_string_data) {
    std::lock_guard<std::mutex> lock(client_mutex);
    std::string action = connected ? "online " : "offline ";
    std::string client_entry = std::to_string(client_int_num) + " " + action + client_info + " " + client_string_data;

    auto it = std::remove_if(client_id_array.begin(), client_id_array.end(), [&](const std::string& entry) { return entry.find(client_info) != std::string::npos; });
    client_id_array.erase(it, client_id_array.end());
    client_id_array.push_back(client_entry);
}

void update_client_int_number() {
    std::lock_guard<std::mutex> lock(client_mutex);
    client_number_id.push_back(client_num_am_id);

    auto magic_number = std::remove(client_number_id.begin(), client_number_id.end(), client_num_am_id);
    client_number_id.erase(magic_number, client_number_id.end());
    client_number_id.push_back(client_num_am_id);
}

void handle_client(int client_socket, std::string client_addr_save) {
    char buffer[MAX_BUFFER] = {0};
    ssize_t bytes_received;
    std::string random_created_string;
    random_created_string.clear();
    random_created_string = generate_random_string(5);
    file_path = screen_shot_save_path + "received_file_" + random_created_string + ".png";
    paths_file_path_ssuser = qnj_screen_shot_path + "received_file_" + random_created_string + ".png";
    bool is_binary = false;

    set_socket_nonblocking(client_socket);

    client_string_data_full = ""; // Initialize client_string_data_full when client connects
    update_client_id_array(client_addr_save, true, client_string_data_full);

    std::ofstream file_output;  // For saving binary data
    bool file_opened = false;   // Track whether the file has been opened

    while (true) {
        bytes_received = recv(client_socket, buffer, MAX_BUFFER, 0);

        if (bytes_received < 0) 
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN) 
            {
                usleep(100000);
                continue;
            }
            std::cerr << "Error in recv() | TCP: " << strerror(errno) << std::endl;
            client_mutex.lock();
            CLIENT_OFFLINE_AMOUNT += 1;
            client_status_map[client_addr_save] = "offline";
            client_mutex.unlock();
            update_client_id_array(client_addr_save, false, client_string_data_full);
            extract_client_vector_data();
            break;
        } 
        else if (bytes_received == 0) 
        {
            client_mutex.lock();
            CLIENT_OFFLINE_AMOUNT += 1;
            CLIENT_ONLINE_AMOUNT = CLIENT_TOTAL_AMOUNT - CLIENT_OFFLINE_AMOUNT;
            save_tcp_server_data_json(CLIENT_TOTAL_AMOUNT, CLIENT_OFFLINE_AMOUNT, CLIENT_ONLINE_AMOUNT);
            client_status_map[client_addr_save] = "offline";
            client_mutex.unlock();
            update_client_id_array(client_addr_save, false, client_string_data_full);
            extract_client_vector_data();
            if (file_opened) {
                file_output.close();
            }
            close(client_socket);
            break;
        }

        // Detect binary data (e.g., based on content inspection or headers)
        if (!is_binary) {
            is_binary = check_if_binary(buffer, bytes_received);
        }

        if (is_binary) {
            // Always reopen file in overwrite mode for each transmission
            if (!file_opened) {
                file_output.open(file_path, std::ios::binary | std::ios::trunc);
                file_opened = true;
            }
            file_output.write(buffer, bytes_received);
            file_output.flush();  // Ensure data is written immediately

            // Close the file when done with the transmission
            if (bytes_received < MAX_BUFFER) {
                file_output.close();
                file_opened = false;  // Ready for next transmission
            }
        } 
        else {
            client_string_data_full += return_client_data(buffer, bytes_received);
            update_client_id_array(client_addr_save, true, client_string_data_full);
            extract_client_vector_data();
        }
    }

    if (file_opened) {
        file_output.close();
    }
}

void QNJ_TCP_HANDLE_CLIENTS(int QNJ_TCP_Main_server_socket) {
    while (true) {
        struct sockaddr_in TCP_client_address;
        socklen_t TCP_client_address_size = sizeof(TCP_client_address);

        TCP_CLIENT_SOCKET = accept(QNJ_TCP_Main_server_socket, (struct sockaddr*)&TCP_client_address, &TCP_client_address_size);

        if (TCP_CLIENT_SOCKET == -1) {
            std::cerr << "[ERR_ACCEPTING_USER_TCP]" << "\n";
            continue;
        }

        std::string client_address = inet_ntoa(TCP_client_address.sin_addr);
        int client_port = ntohs(TCP_client_address.sin_port);
        std::string client_addr_save = client_address + ":" + std::to_string(client_port);

        QNJ_TCP_CLIENT_SOCKET.push_back(TCP_CLIENT_SOCKET);

        std::cout << "New client addres: " << client_addr_save << std::endl;

        client_mutex.lock();
        CLIENT_TOTAL_AMOUNT += 1;
        CLIENT_ONLINE_AMOUNT = CLIENT_TOTAL_AMOUNT - CLIENT_OFFLINE_AMOUNT;
        save_tcp_server_data_json(CLIENT_TOTAL_AMOUNT, CLIENT_OFFLINE_AMOUNT, CLIENT_ONLINE_AMOUNT);
        client_status_map[client_addr_save] = "online";
        client_int_num += 1;
        client_num_am_id += 1;
        client_mutex.unlock();

        update_client_id_array(client_addr_save, true, "");
        update_client_int_number();
        std::thread client_thread([&]() { handle_client(TCP_CLIENT_SOCKET, client_addr_save); });
        client_thread.detach();
    }
}

#endif