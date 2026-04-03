#ifndef PLAYLIST_RENDERER_H
#define PLAYLIST_RENDERER_H

#include "../model/IPlaylistVisitor.h"
#include "../view/IPlayerView.h"
#include <vector>
#include <string>

class PlaylistRenderer final : public IPlaylistVisitor {
private:
    IPlayerView& view_;
    std::vector<std::string> names_;

public:
    explicit PlaylistRenderer(IPlayerView& view);
    void visit(const std::string& name, const std::string& path) override;
    void render() const;
};

#endif //PLAYLIST_RENDERER_H