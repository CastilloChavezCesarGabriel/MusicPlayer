#include "model/repeat/RepeatOneMode.h"

RepeatOneMode::RepeatOneMode() : RepeatStrategy(1) {}

bool RepeatOneMode::apply(Playlist&, IPlaybackListener&) { return true; }