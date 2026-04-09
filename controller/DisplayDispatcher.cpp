#include "DisplayDispatcher.h"

DisplayDispatcher::DisplayDispatcher(MusicPlayer& musicPlayer, IDisplayView& view)
    : music_player_(musicPlayer), view_(view),
      sort_(musicPlayer, view), search_(musicPlayer, view) {}

void DisplayDispatcher::sort() {
    sort_.cycle();
}

void DisplayDispatcher::search(const std::string& query) {
    search_.search(query);
}

void DisplayDispatcher::pick(const std::string& name) {
    music_player_.pick(name);
    view_.dismiss();
}
