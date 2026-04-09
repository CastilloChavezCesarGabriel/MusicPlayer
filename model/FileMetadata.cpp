#include "FileMetadata.h"
#include <filesystem>

FileMetadata::FileMetadata(const std::string& path) : path_(path) {}

bool FileMetadata::exists() const {
    return std::filesystem::exists(path_);
}

long long FileMetadata::stamp() const {
    if (!exists()) return 0;
    const auto time = std::filesystem::last_write_time(path_);
    return time.time_since_epoch().count();
}

int FileMetadata::last() const {
    if (!exists()) return 0;
    return static_cast<int>(std::filesystem::file_size(path_));
}