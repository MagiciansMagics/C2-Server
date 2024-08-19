#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::string get_username_from_database() {
    std::ifstream file("/root/qnj-server/database.log");
    if (!file.is_open()) {
        std::cerr << "Error opening file, database.log" << "\n";
        return "none"; // Return a default value if file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        if (std::getline(ss, token, ',')) {
            file.close(); // Close file once token is found
            return token;
        }
    }

    file.close();
    return "none";
}