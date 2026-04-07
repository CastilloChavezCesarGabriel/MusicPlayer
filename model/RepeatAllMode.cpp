#include "RepeatAllMode.h"

void RepeatAllMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    } else {
        playlist.select(0, listener);
    }
}

void RepeatAllMode::announce(IPlaybackListener& listener) const {
    listener.onRepeatChanged(2);
}
