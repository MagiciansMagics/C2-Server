#ifndef _PARSE_PAGE_HPP_
#define _PARSE_PAGE_HPP_

std::string parsePostData(const std::string& requestHeaders, const std::string& key) 
{

    size_t pos = requestHeaders.find("\r\n\r\n");
    if (pos == std::string::npos) {
        std::cout << "No body found" << "\n";
        return "none";
    }

    std::string body = requestHeaders.substr(pos + 4); // Skip "\r\n\r\n"

    // Find the position of the key in the query string
    size_t keyPos = body.find(key);
    if (keyPos != std::string::npos) {
        // Find the position of the '=' character after the key
        size_t equalPos = body.find('=', keyPos);
        if (equalPos != std::string::npos) {
            // Find the position of the '&' character after the '=' character
            size_t ampersandPos = body.find('&', equalPos);
            if (ampersandPos != std::string::npos) {
                // Extract the substring between '=' and '&' as the value
                return body.substr(equalPos + 1, ampersandPos - equalPos - 1);
            } else {
                // If '&' is not found, extract the substring from '=' to the end of the string
                return body.substr(equalPos + 1);
            }
        }
    }
    // Return an empty string if key is not found or if value extraction fails
    return "";
}

#endif