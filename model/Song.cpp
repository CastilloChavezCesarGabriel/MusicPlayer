#include "Song.h"
#include <regex>

Song::Song(const std::string& name, const std::string& path)
       : name_(name), path_(path) {
}

void Song::accept(IPlaylistVisitor& visitor) const {
    visitor.visit(name_, path_);
}

bool Song::match(const std::string& query) const {
    return name_.find(query) != std::string::npos;
}

std::string Song::parse(const std::string& name) {
    static const std::regex pattern(R"(\(\d+\)\s(.+))");
    std::smatch match;
    if (std::regex_match(name, match, pattern)) {
        return trim(match[1]);
    }
    return trim(name);
}

int Song::order(const std::string& name) {
    static const std::regex pattern(R"(^\s*[\(\[]?(\d+)[\)\]]?[\s\-_:]*)");
    std::smatch match;
    if (std::regex_search(name, match, pattern)) {
        return std::stoi(match[1]);
    }
    return 0;
}

std::string Song::trim(const std::string& string) {
    const size_t first = string.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    const size_t last = string.find_last_not_of(" \t\n\r");
    return string.substr(first, last - first + 1);
}