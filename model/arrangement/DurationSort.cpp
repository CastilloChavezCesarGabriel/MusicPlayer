#include "model/arrangement/DurationSort.h"
#include "model/core/FileMetadata.h"

void DurationSort::visit(const std::string&, const std::string& path) {
    key_ = FileMetadata(path).last();
}