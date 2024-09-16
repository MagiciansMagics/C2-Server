#ifndef _SAVE_CLIENT_DATA_0x00_HPP_
#define _SAVE_CLIENT_DATA_0x00_HPP_
#include "../qnj_config.h"
#include "../networking/utils/generate_random_string.hpp"

void save_client_data_0x00(const std::string& first_name, const std::string& last_name, const std::string age, const std::string& gender, const std::string& email, const std::string& phonenumber, const std::string& country, const std::string& city, const std::string children_amount, const std::string& material_status, const std::string& user_mugshot_pic)
{
    std::fstream file(data_0x00_client_path, std::ios::in); // Open file for reading

    if (!file.is_open()) return;

    std::vector<std::string> lines;
    std::string line;

    std::string json_file_data;
    json_file_data += ",   \"user-" + generate_random_string(5) + "\":\n";
    json_file_data += "    {\n";
    json_file_data += "        \"first_name\": \"" + first_name + "\",\n";
    json_file_data += "        \"last_name\": \"" + last_name + "\",\n";
    json_file_data += "        \"age\": \"" + age + "\",\n";
    json_file_data += "        \"gender\": \"" + gender + "\",\n";
    json_file_data += "        \"email\": \"" + email + "\",\n";
    json_file_data += "        \"phonenumber\": \"" + phonenumber + "\",\n";
    json_file_data += "        \"country\": \"" + country + "\",\n";
    json_file_data += "        \"city\": \"" + city + "\",\n";
    json_file_data += "        \"children_amount\": \"" + children_amount + "\",\n";
    json_file_data += "        \"material_status\": \"" + material_status + "\",\n";
    json_file_data += "        \"user_mugpic\": \"" + user_mugshot_pic + "\"\n";
    json_file_data += "    }";

    // Read the file line by line and store in the vector
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    
    file.close(); // Close the file after reading

    // Process each line
    for (auto& p : lines)
    {
        auto closing_brace_pos = p.find("}");
        if (closing_brace_pos != std::string::npos)
        {
            if (closing_brace_pos == 4)
            {
                size_t next_char_pos = closing_brace_pos + 2;

                p.insert(next_char_pos, json_file_data);

                break; // Break after inserting the data
            }
        }
    }

    // Open the file again for writing (truncate)
    std::ofstream outfile(data_0x00_client_path, std::ios::trunc);

    if (!outfile.is_open()) return;

    for (const auto& modified_line : lines)
    {
        outfile << modified_line << "\n";
    }

    outfile.close();
}

#endif