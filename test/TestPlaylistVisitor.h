#ifndef TEST_PLAYLIST_VISITOR_H
#define TEST_PLAYLIST_VISITOR_H

#include "../model/IPlaylistVisitor.h"
#include <string>
#include <vector>

class TestPlaylistVisitor final : public IPlaylistVisitor {
private:
    std::vector<std::string> names_;
    std::vector<std::string> paths_;

public:
    void visit(const std::string& name, const std::string& path) override;

    bool hasName(const std::string& name) const;
    bool hasPath(const std::string& path) const;
    bool isEmpty() const;
    bool hasSongs(int expected) const;
    bool hasNameAt(int index, const std::string& name) const;
};

#endif //TEST_PLAYLIST_VISITOR_H
