#ifndef _QNJ_SERVER_H
#define _QNJ_SERVER_H

#include "./src/qnj_config.h"
#include "./src/server_1/MAIN_server.hpp"
#include "./src/server_1/MAIN_handle_client.hpp"
#include "./src/server_2/TCP_server.hpp"
#include "./src/server_2/TCP_handle_client.hpp"
#include "./config/json/json_config_loader.hpp"

std::vector<pid_t> worker_pids;

void listen(const std::string& address, const int port)
{
    std::cout << "[+] HTTP Server listening on: " << address << ":" << port << "\n";
    SERVER_MAIN_QNJ();
    BIND_SERVER_QNJ(address, port);
    LISTEN_SERVER_QNJ();
    CLIENTM_main_server_hpp(QNJ_Main_server_socket);
}

void tcp_listen(const std::string& address, const int port)
{
    std::cout << "[+] TCP Server listening on: " << address << ":" << port << "\n";
    QNJ_TCP_MAIN_SOCKET();
    QNJ_TCP_BIND_SOCKET(address, port);
    QNJ_TCP_LISTEN_SOCKET();
    QNJ_TCP_HANDLE_CLIENTS(QNJ_TCP_Main_server_socket);
}

/*
void spawn_worker(void(*server_func)(const std::string&, const int), const std::string& ip, const int port) {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Failed to fork worker process\n";
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // Child process: Start the server
        server_func(ip, port);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process: Save the child's PID
        worker_pids.push_back(pid);
    }
}

void monitor_workers() {
    while (true) {
        pid_t pid = wait(NULL); // Wait for any child process to terminate
        if (pid > 0) {
            std::cout << "Worker process " << pid << " exited. Restarting...\n";
            // Remove the terminated worker from the list and spawn a new one
            worker_pids.erase(std::remove(worker_pids.begin(), worker_pids.end(), pid), worker_pids.end());
            // Depending on which server you want to restart, call spawn_worker() with the appropriate function
            // For example, if you want to restart the HTTP server:
            spawn_worker(listen, "127.0.0.1", 3200); // Replace with actual IP and port
            // If you want to restart the TCP server, call spawn_worker() with tcp_listen() instead
        }
    }
}

*/

void start_both_servers(const std::string& http_ip, const int http_port, const std::string& tcp_ip, const int tcp_port)
{
    std::thread start_http_server([&]() { listen(http_ip, http_port); });
    sleep(0.7);
    std::thread start_tcp_server([&]() { tcp_listen(tcp_ip, tcp_port); });
    sleep(0.7);
    std::thread load_json_config_files([&]() { load_json_configs(); });
    sleep(0.7);

    start_http_server.join();
    start_tcp_server.join();
    load_json_config_files.join();

    // Monitor the worker processes
}

#endif