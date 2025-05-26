#include "Hash.h"
#include <openssl/sha.h>
#include <iomanip>
#include <iostream>

Hash::Hash() = default;

std::string Hash::generate(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::ostringstream hexadecimalStream;
    for (const unsigned char i : hash) {
        hexadecimalStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    return hexadecimalStream.str();
}

std::string Hash::generate(const int input) {
    return generate(std::to_string(input));
}
