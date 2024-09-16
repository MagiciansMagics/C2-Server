#include "../send_html_client_side.hpp"

bool isPNG(const char* buffer, size_t bufferSize) {
    // PNG signature: 89 50 4E 47 0D 0A 1A 0A
    const unsigned char pngSignature[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

    // Ensure the buffer is at least as large as the PNG signature
    if (bufferSize < sizeof(pngSignature)) {
        return false;
    }

    // Compare the first 8 bytes of the buffer with the PNG signature
    if (memcmp(buffer, pngSignature, sizeof(pngSignature)) == 0) {
        return true; // Buffer starts with the PNG signature
    }

    return false; // No match
}


bool check_if_binary(const char* data, ssize_t size) {
    for (ssize_t i = 0; i < size; i++) {
        // Check for non-printable characters as an indicator of binary data
        if (data[i] < 0x20 && data[i] != '\n' && data[i] != '\r' && data[i] != '\t') {
            return true;
        }
    }
    return false;
}
