#ifndef HASH_H
#define HASH_H
#include <string>
#include <sstream>

class Hash {
public:
    Hash();
    static std::string generate(const std::string& input);
    static std::string generate(int input);
};

#endif //HASH_H
