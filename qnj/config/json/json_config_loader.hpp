#ifndef _JSON_CONFIG_LOADER_HPP_
#define _JSON_CONFIG_LOADER_HPP_

void load_json_configs()
{
    std::ofstream server_data("/root/qnj-server/server_data.json");
    std::ofstream tcp_se_data("/root/qnj-server/tcp_connections_database.json");
    std::ofstream client_connection_data("/root/qnj-server/save_client_connection.log");

    std::string server_data_val = "{\n";
    server_data_val += "    \"requests\": \"0\"\n";
    server_data_val += "}";

    std::string tcp_server_data = "{\n";
    tcp_server_data += "    \"total_clients\": \"0\",\n";
    tcp_server_data += "    \"offline_clients\": \"0\",\n";
    tcp_server_data += "    \"online_clients\": \"0\"\n";
    tcp_server_data += "}";

    std::string none = "";

    client_connection_data << none;

    server_data << server_data_val;
    tcp_se_data << tcp_server_data;

    server_data.close();
    tcp_se_data.close();
}

#endif