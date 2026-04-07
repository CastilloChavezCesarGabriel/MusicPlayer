#include "NoRepeatMode.h"

NoRepeatMode::NoRepeatMode() : RepeatStrategy(0) {}

void NoRepeatMode::apply(Playlist& playlist, IPlaybackListener& listener) {
    if (playlist.hasNext()) {
        playlist.advance(listener);
    }
}
