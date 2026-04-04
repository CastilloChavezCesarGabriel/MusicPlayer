#include "PlaybackNotifier.h"

void PlaybackNotifier::add(IPlaybackListener& listener) {
    listeners_.push_back(&listener);
}

void PlaybackNotifier::onStart(const std::string& path) {
    for (auto* listener : listeners_) {
        listener->onStart(path);
    }
}

void PlaybackNotifier::onChanged() {
    for (auto* listener : listeners_) {
        listener->onChanged();
    }
}

void PlaybackNotifier::onSelected(const int index) {
    for (auto* listener : listeners_) {
        listener->onSelected(index);
    }
}

void PlaybackNotifier::onEnabled(const bool state) {
    for (auto* listener : listeners_) {
        listener->onEnabled(state);
    }
}

void PlaybackNotifier::onReveal(const bool visible) {
    for (auto* listener : listeners_) {
        listener->onReveal(visible);
    }
}

void PlaybackNotifier::onSchedule(const int delay) {
    for (auto* listener : listeners_) {
        listener->onSchedule(delay);
    }
}

void PlaybackNotifier::onCancel() {
    for (auto* listener : listeners_) {
        listener->onCancel();
    }
}

void PlaybackNotifier::onRepeatChanged(const int mode) {
    for (auto* listener : listeners_) {
        listener->onRepeatChanged(mode);
    }
}

void PlaybackNotifier::onFeedback(const std::string& message, const bool success) {
    for (auto* listener : listeners_) {
        listener->onFeedback(message, success);
    }
}