#include "PlaylistRenderer.h"

PlaylistRenderer::PlaylistRenderer(IPlayerView& view)
    : view_(view) {
}

void PlaylistRenderer::visit(const std::string& name, const std::string&) {
    names_.push_back(name);
}

void PlaylistRenderer::render() const {
    view_.refresh(names_);
}