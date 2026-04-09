#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {}

void SearchController::search(const std::string& query) const {
    if (query.empty()) {
        view_.dismiss();
        return;
    }
    PlaylistRenderer renderer(view_);
    music_player_.search(query, renderer);
    renderer.suggest();
}