#include "model/arrangement/DateSort.h"
#include "model/core/FileMetadata.h"

void DateSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).stamp();
}