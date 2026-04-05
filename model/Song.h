#ifndef SONG_H
#define SONG_H

#include "IPlaylistVisitor.h"
#include <string>

class Song {
private:
    std::string name_;
    std::string path_;

    static std::string trim(const std::string& string);

public:
    Song(const std::string& name, const std::string& path);

    void accept(IPlaylistVisitor& visitor) const;
    bool matches(const std::string& query) const;
    bool isEqualTo(const Song& other) const;
    static std::string parse(const std::string& name);
    static long long stamp(const std::string& path);
    static int last(const std::string& path);
};

#endif //SONG_H