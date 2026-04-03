#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Song.h"
#include "IPlaylistVisitor.h"
#include <string>
#include <vector>

class MusicLibrary final : public IPlaylistVisitor {
private:
    std::string music_path_;

public:
    explicit MusicLibrary(const std::string& musicPath);

    std::vector<Song> load() const;
    Song import(const std::string& sourcePath) const;
    void visit(const std::string& name, const std::string& path) override;
    bool contains(const std::string& filename) const;
    static std::vector<std::string> scan(const std::string& directory);
    static bool isSupported(const std::string& fileName);
};

#endif //MUSIC_LIBRARY_H