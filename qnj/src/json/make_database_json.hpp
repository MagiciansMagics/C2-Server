#include "../qnj_config.h"
using namespace std;

std::string get_time_nu()
{
    time_t now = time(0);
    struct tm timeinfo;
    char time_buffer[80];
    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(time_buffer, sizeof(time_buffer), "%d/%b/%Y %T", &timeinfo);

    return std::string(time_buffer);
}

void save_server_data_json(int& request_amount) 
{
    // Create and open a text filestring
    ofstream MyFile("/root/qnj-server/server_data.json");

    // Write to the file
    
    std::string time_var_data = get_time_nu();

    std::string request_var = "{\n";
    request_var += "    \"requests\": \"" + std::to_string(request_amount) + "\",\n";
    request_var += "    \"time_var\": \"" + time_var_data + "\"\n";
    request_var += "}\n";
    MyFile << request_var;

    // Close the file
    MyFile.close();
}