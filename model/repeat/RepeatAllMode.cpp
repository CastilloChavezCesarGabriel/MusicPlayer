#include "model/repeat/RepeatAllMode.h"

RepeatAllMode::RepeatAllMode() : RepeatStrategy(2) {}

bool RepeatAllMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    } else {
        playlist.select(0, listener);
    }
    return true;
}