#ifndef _PARSE_FILE_HPP_
#define _PARSE_FILE_HPP_

#include <string>
#include <iostream>

std::string parseFileData(const std::string& requestHeaders, const std::string& key) 
{
    // The boundary string used in the multipart form data
    std::string boundary = "";
    size_t boundaryPos = requestHeaders.find("boundary=");
    if (boundaryPos != std::string::npos) {
        boundary = "--" + requestHeaders.substr(boundaryPos + 9); // Skip "boundary="
    } else {
        std::cout << "Boundary not found" << "\n";
        return "none";
    }

    // Locate the start of the body content
    size_t bodyPos = requestHeaders.find("\r\n\r\n");
    if (bodyPos == std::string::npos) {
        std::cout << "No body found" << "\n";
        return "none";
    }

    std::string body = requestHeaders.substr(bodyPos + 4); // Skip "\r\n\r\n"

    size_t startBoundaryPos = body.find(boundary);
    while (startBoundaryPos != std::string::npos) {
        // Move past the boundary line
        startBoundaryPos += boundary.length() + 2; // Skip boundary + "\r\n"

        // Check if this part contains the key
        size_t namePos = body.find("name=\"" + key + "\"", startBoundaryPos);
        if (namePos != std::string::npos && namePos < body.find(boundary, startBoundaryPos)) {
            // Locate the end of the header section for this part
            size_t fileDataPos = body.find("\r\n\r\n", namePos);
            if (fileDataPos == std::string::npos) {
                std::cout << "File data start not found" << "\n";
                return "none";
            }

            // Skip the header section and go to the start of the file content
            fileDataPos += 4; // Skip "\r\n\r\n"

            // Locate the ending boundary for the file content
            size_t endBoundaryPos = body.find(boundary, fileDataPos);
            if (endBoundaryPos == std::string::npos) {
                std::cout << "End boundary not found" << "\n";
                return "none";
            }

            // Extract the file content
            std::string fileContent = body.substr(fileDataPos, endBoundaryPos - fileDataPos - 2); // -2 to remove trailing "\r\n"

            return fileContent;
        }

        // Move to the next part if the current part does not contain the key
        startBoundaryPos = body.find(boundary, startBoundaryPos);
    }

    std::cout << "Key not found" << "\n";
    return "none";
}

#endif
