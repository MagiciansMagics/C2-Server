void signup_parsePostData(const std::string& requestHeaders, std::string& password, std::string& email) 
{
    // Find the position of the empty line separating headers from body
    size_t pos = requestHeaders.find("\r\n\r\n");
    if (pos == std::string::npos) {
        // No body found
        return;
    }

    // Extract the body from the request headers
    std::string body = requestHeaders.substr(pos + 4); // Skip "\r\n\r\n"

    // Split the body into key-value pairs
    std::istringstream iss(body);
    std::string pair;
    while (std::getline(iss, pair, '&')) {
        size_t equalsPos = pair.find("=");
        if (equalsPos != std::string::npos) {
            std::string key = pair.substr(0, equalsPos);
            std::string value = pair.substr(equalsPos + 1);
            if (key == "QNJ-EMAIL-SINGUP") 
            {
                email = value;
            } 
            else if (key == "QNJ-PASSWORD-SINGUP") 
            {
                password = value;
            }
        }
    }
}