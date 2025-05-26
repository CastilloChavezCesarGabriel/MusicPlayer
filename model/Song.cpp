#include "Song.h"
#include "Hash.h"
#include <regex>

Song::Song(const int number, const std::string &name, const std::string &path)
       : number_(number), name_(name), path_(path) {
    id_ = Hash::generate(std::to_string(number) + name + path);
}

int Song::getNumber() const {
    return number_;
}

std::string Song::getId() const {
    return id_;
}

std::string Song::getName() const {
    return name_;
}

std::string Song::getFilePath() const {
    return path_;
}

int Song::extractNumber(const std::string &name) {
    static const std::regex numberRegex(R"(^\s*[\(\[]?(\d+)[\)\]]?[\s\-_:]*)");
    std::smatch match;
    if (std::regex_search(name, match, numberRegex)) {
        return std::stoi(match[1]);
    }
    return 0;
}

std::string Song::extractName(const std::string &name) {
    static const std::regex nameRegex(R"(\(\d+\)\s(.+))");
    std::smatch match;
    if (std::regex_match(name, match, nameRegex)) {
        return trim(match[1]);
    }
    return trim(name);
}

std::string Song::trim(const std::string &string) {
    const size_t first = string.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";

    const size_t last = string.find_last_not_of(" \t\n\r");
    return string.substr(first, last - first + 1);
}

bool Song::match(const Song& song, const std::string& query) {
    const std::string name = song.getName();
    return name.find(query) != std::string::npos;
}