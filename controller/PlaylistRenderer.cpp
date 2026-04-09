#include "PlaylistRenderer.h"

PlaylistRenderer::PlaylistRenderer(IDisplayView& view)
    : view_(view) {
}

void PlaylistRenderer::visit(const std::string& name, const std::string&) {
    names_.push_back(name);
}

void PlaylistRenderer::render() const {
    view_.refresh(names_);
}

void PlaylistRenderer::suggest() const {
    view_.suggest(names_);
}
