#include "DurationSort.h"

void DurationSort::visit(const std::string&, const std::string& path) {
    key_ = Song::last(path);
}