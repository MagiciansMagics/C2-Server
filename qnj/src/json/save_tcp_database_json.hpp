#include "../qnj_config.h"

void save_tcp_server_data_json(int total_amount_client, int offline_amount_clients, int online_amount_clients)
{
    std::ofstream tcp_database_file("/root/qnj-server/tcp_connections_database.json");

    std::string database_connection = "{\n";
    database_connection += "    \"total_clients\": \"" + std::to_string(total_amount_client) + "\",\n";
    database_connection += "    \"offline_clients\": \"" + std::to_string(offline_amount_clients) + "\",\n";
    database_connection += "    \"online_clients\": \"" + std::to_string(online_amount_clients) + "\"\n";
    database_connection += "}";

    tcp_database_file << database_connection;

    tcp_database_file.close();
}