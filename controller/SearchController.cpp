#include "SearchController.h"
#include "PlaylistRenderer.h"

SearchController::SearchController(Model& model, IPlayerView& view)
    : model_(model), view_(view) {}

void SearchController::search(const std::string& query) {
    if (query.empty()) {
        view_.dismiss();
        return;
    }
    PlaylistRenderer renderer(view_);
    model_.search(query, renderer);
    renderer.suggest();
}
