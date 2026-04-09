#include "model/repeat/NoRepeatMode.h"

NoRepeatMode::NoRepeatMode() : RepeatStrategy(0) {}

bool NoRepeatMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (!playlist.hasNext()) return false;
    playlist.advance(listener);
    return true;
}