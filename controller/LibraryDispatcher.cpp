#include "LibraryDispatcher.h"

LibraryDispatcher::LibraryDispatcher(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {}

void LibraryDispatcher::onAdd() {
    const std::string path = view_.browse();
    if (!path.empty()) {
        music_player_.insert(path);
    }
}

void LibraryDispatcher::onRemove(const int index) {
    if (view_.confirm("Are you sure you wanna delete this song?")) {
        music_player_.remove(index);
    }
}

void LibraryDispatcher::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        music_player_.insert(path);
    }
}
