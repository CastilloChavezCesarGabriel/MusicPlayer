#ifndef I_PLAYLIST_VISITOR_H
#define I_PLAYLIST_VISITOR_H
#include <string>

class IPlaylistVisitor {
public:
    virtual ~IPlaylistVisitor() = default;
    virtual void visit(const std::string& name, const std::string& path) = 0;
};

#endif //I_PLAYLIST_VISITOR_H