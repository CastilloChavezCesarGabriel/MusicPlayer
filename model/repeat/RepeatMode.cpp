#include "model/repeat/RepeatMode.h"

RepeatMode::RepeatMode(Playlist& playlist, PlaybackNotifier& notifier)
    : playlist_(playlist), notifier_(notifier) {}

void RepeatMode::add(std::unique_ptr<RepeatStrategy> strategy) {
    modes_.push_back(std::move(strategy));
}

void RepeatMode::advance() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->announce(notifier_);
}

bool RepeatMode::apply() const {
    return modes_[index_]->apply(playlist_, notifier_);
}