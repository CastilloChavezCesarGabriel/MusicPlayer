#include "TestPlaylistVisitor.h"
#include <algorithm>

void TestPlaylistVisitor::visit(const std::string& name, const std::string& path) {
    names_.push_back(name);
    paths_.push_back(path);
}

bool TestPlaylistVisitor::hasName(const std::string& name) const {
    return std::ranges::find(names_, name) != names_.end();
}

bool TestPlaylistVisitor::hasPath(const std::string& path) const {
    return std::ranges::find(paths_, path) != paths_.end();
}

bool TestPlaylistVisitor::isEmpty() const {
    return names_.empty();
}

bool TestPlaylistVisitor::hasSongs(const int expected) const {
    return names_.size() == expected;
}

bool TestPlaylistVisitor::hasNameAt(const int index, const std::string& name) const {
    return index >= 0 && index < names_.size() && names_[index] == name;
}
