#ifndef FILE_METADATA_H
#define FILE_METADATA_H

#include <string>

class FileMetadata {
private:
    std::string path_;

    bool exists() const;

public:
    explicit FileMetadata(const std::string& path);
    long long stamp() const;
    int last() const;
};

#endif //FILE_METADATA_H