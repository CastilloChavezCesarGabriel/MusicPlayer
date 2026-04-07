#include "RepeatAllMode.h"

RepeatAllMode::RepeatAllMode() : RepeatStrategy(2) {}

void RepeatAllMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    } else {
        playlist.select(0, listener);
    }
}