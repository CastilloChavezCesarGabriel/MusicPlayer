#include "DisplayDispatcher.h"

DisplayDispatcher::DisplayDispatcher(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view),
      sort_(musicPlayer, view), search_(musicPlayer, view) {}

void DisplayDispatcher::onSort() {
    sort_.cycle();
}

void DisplayDispatcher::onSearch(const std::string& query) {
    search_.search(query);
}

void DisplayDispatcher::onPick(const std::string& name) {
    music_player_.pick(name);
    view_.dismiss();
}

void DisplayDispatcher::onAdjust(const int volume) {
    view_.adjust(volume);
}
