#include "DurationSort.h"
#include "FileMetadata.h"

void DurationSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).last();
}