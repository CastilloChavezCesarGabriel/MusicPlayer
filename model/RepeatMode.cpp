#include "RepeatMode.h"
#include "NoRepeatMode.h"
#include "RepeatOneMode.h"
#include "RepeatAllMode.h"

RepeatMode::RepeatMode(Playlist& playlist, PlaybackNotifier& notifier)
    : playlist_(playlist), notifier_(notifier) {
    modes_.push_back(std::make_unique<NoRepeatMode>());
    modes_.push_back(std::make_unique<RepeatOneMode>());
    modes_.push_back(std::make_unique<RepeatAllMode>());
}

void RepeatMode::advance() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->announce(notifier_);
}

void RepeatMode::apply() {
    modes_[index_]->apply(playlist_, notifier_);
}
