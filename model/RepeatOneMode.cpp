#include "RepeatOneMode.h"

void RepeatOneMode::apply(Playlist&, IPlaybackListener&) {
}

void RepeatOneMode::announce(IPlaybackListener& listener) const {
    listener.onRepeatChanged(1);
}
