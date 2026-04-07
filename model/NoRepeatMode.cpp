#include "NoRepeatMode.h"

void NoRepeatMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    }
}

void NoRepeatMode::announce(IPlaybackListener& listener) const {
    listener.onRepeatChanged(0);
}
