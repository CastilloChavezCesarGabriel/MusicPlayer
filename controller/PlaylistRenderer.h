#ifndef PLAYLIST_RENDERER_H
#define PLAYLIST_RENDERER_H

#include "model/events/IPlaylistVisitor.h"
#include "../view/IDisplayView.h"
#include <vector>
#include <string>

class PlaylistRenderer final : public IPlaylistVisitor {
private:
    IDisplayView& view_;
    std::vector<std::string> names_;

public:
    explicit PlaylistRenderer(IDisplayView& view);
    void visit(const std::string& name, const std::string& path) override;
    void render() const;
    void suggest() const;
};

#endif //PLAYLIST_RENDERER_H
