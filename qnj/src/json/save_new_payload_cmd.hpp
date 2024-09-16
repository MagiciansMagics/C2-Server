#include "../qnj_config.h"

void save_new_payload_cmd(const std::string& command_name, const std::string& command_file)
{
    std::ofstream file(payload_config_path, std::ios::app);

    file << command_name + " = ";
    
    file << payload_file_path + command_file + "\n";
}