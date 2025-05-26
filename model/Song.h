#ifndef SONG_H
#define SONG_H
#include <string>

class Song {
private:
    int number_;
    std::string id_;
    std::string name_;
    std::string path_;

    static std::string trim(const std::string &string);

public:
    Song(int number, const std::string &name, const std::string &path);

    int getNumber() const;
    std::string getId() const;
    std::string getName() const;
    std::string getFilePath() const;
    static std::string extractName(const std::string &name);
    static int extractNumber(const std::string &name);
    static bool match(const Song& song, const std::string& query);
};

#endif //SONG_H
