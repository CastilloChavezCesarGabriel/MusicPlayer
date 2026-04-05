#include "DateSort.h"

void DateSort::visit(const std::string&, const std::string& path) {
    key_ = Song::stamp(path);
}