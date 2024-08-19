#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

// Function to trim whitespace from both ends of a string
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to load the command-to-path mappings from a configuration file
bool loadConfig(const std::string &filename, std::unordered_map<std::string, std::string> &cmdMap) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "Error opening configuration file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        // Remove any leading or trailing whitespace from the line
        line = trim(line);

        // Skip empty lines and lines starting with a comment
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Find the position of the equals sign
        size_t pos = line.find('=');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line in configuration file: " << line << std::endl;
            continue;
        }

        // Extract the command and the path
        std::string cmd = trim(line.substr(0, pos));
        std::string path = trim(line.substr(pos + 1));

        // Store the mapping in the map
        cmdMap[cmd] = path;
    }

    configFile.close();
    return true;
}

int main() {
    // Create a map to hold command-to-path mappings
    std::unordered_map<std::string, std::string> cmdMap;

    // Load the configuration file
    if (!loadConfig("commands.cfg", cmdMap)) {
        return 1;  // Exit if the configuration file couldn't be loaded
    }

    std::string inputCmd;

    // Continuously prompt for commands until "exit" is entered
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, inputCmd);

        // Trim the input command
        inputCmd = trim(inputCmd);

        // Check if the user wants to exit
        if (inputCmd == "exit") {
            break;
        }

        // Find the command in the map
        auto it = cmdMap.find(inputCmd);
        if (it != cmdMap.end()) {
            // Output the corresponding file path
            std::cout << "File path: " << it->second << std::endl;
        } else {
            std::cout << "Command not found!" << std::endl;
        }
    }

    return 0;
}
