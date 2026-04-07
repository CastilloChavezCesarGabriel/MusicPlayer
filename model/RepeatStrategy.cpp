#include "RepeatStrategy.h"

RepeatStrategy::RepeatStrategy(const int code) : code_(code) {}

void RepeatStrategy::announce(IPlaybackListener& listener) const {
    listener.onRepeatChanged(code_);
}