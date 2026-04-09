#include "DisplayBridge.h"
#include "PlaylistRenderer.h"

DisplayBridge::DisplayBridge(MusicPlayer& musicPlayer, IDisplayView& view)
    : music_player_(musicPlayer), view_(view) {
    render();
}

void DisplayBridge::onChanged() { render(); }

void DisplayBridge::onSelected(const int index) { view_.highlight(index); }

void DisplayBridge::render() const {
    PlaylistRenderer renderer(view_);
    music_player_.accept(renderer);
    renderer.render();
}
