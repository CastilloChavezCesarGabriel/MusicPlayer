#include "DateSort.h"
#include "FileMetadata.h"

void DateSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).stamp();
}