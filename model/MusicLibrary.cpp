#include "MusicLibrary.h"
#include <filesystem>

MusicLibrary::MusicLibrary(const std::string& musicPath)
    : music_path_(musicPath) {
}

std::vector<std::string> MusicLibrary::scan(const std::string& directory) {
    std::vector<std::string> result;
    if (!std::filesystem::exists(directory)) return result;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && isSupported(entry.path().string())) {
            result.push_back(entry.path().string());
        }
    }
    return result;
}

std::vector<Song> MusicLibrary::load() const {
    std::vector<Song> songs;
    for (const auto& path : scan(music_path_)) {
        const std::string filename = std::filesystem::path(path).filename().string();
        songs.emplace_back(filename, path);
    }
    return songs;
}

Song MusicLibrary::import(const std::string& sourcePath) const {
    const std::filesystem::path source(sourcePath);
    const std::string filename = source.filename().string();
    const std::filesystem::path destination = std::filesystem::path(music_path_) / filename;

    if (!std::filesystem::exists(destination)) {
        std::filesystem::copy_file(source, destination);
    }

    return Song(filename, destination.string());
}



void MusicLibrary::visit(const std::string&, const std::string& path) {
    std::filesystem::remove(path);
}

bool MusicLibrary::contains(const std::string& filename) const {
    const std::filesystem::path destination = std::filesystem::path(music_path_) / filename;
    return std::filesystem::exists(destination);
}

bool MusicLibrary::isSupported(const std::string& fileName) {
    const std::filesystem::path path(fileName);
    const std::string extension = path.extension().string();
    return extension == ".mp3" || extension == ".wav";
}