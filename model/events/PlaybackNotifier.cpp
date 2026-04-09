#include "model/events/PlaybackNotifier.h"

void PlaybackNotifier::add(IPlaybackListener& listener) {
    listeners_.push_back(&listener);
}

void PlaybackNotifier::notify(const std::function<void(IPlaybackListener*)>& action) const {
    for (auto* listener : listeners_) {
        action(listener);
    }
}

void PlaybackNotifier::onStart(const std::string& path) {
    notify([&](IPlaybackListener* listener) {
        listener->onStart(path);
    });
}

void PlaybackNotifier::onChanged() {
    notify([](IPlaybackListener* listener) {
        listener->onChanged();
    });
}

void PlaybackNotifier::onSelected(const int index) {
    notify([&](IPlaybackListener* listener) {
        listener->onSelected(index);
    });
}

void PlaybackNotifier::onEnabled(const bool state) {
    notify([&](IPlaybackListener* listener) {
        listener->onEnabled(state);
    });
}

void PlaybackNotifier::onReveal(const bool visible) {
    notify([&](IPlaybackListener* listener) {
        listener->onReveal(visible);
    });
}

void PlaybackNotifier::onSchedule(const int delay) {
    notify([&](IPlaybackListener* listener) {
        listener->onSchedule(delay);
    });
}

void PlaybackNotifier::onCancel() {
    notify([](IPlaybackListener* listener) {
        listener->onCancel();
    });
}

void PlaybackNotifier::onRepeatChanged(const int mode) {
    notify([&](IPlaybackListener* listener) {
        listener->onRepeatChanged(mode);
    });
}

void PlaybackNotifier::onFeedback(const std::string& message, const bool success) {
    notify([&](IPlaybackListener* listener) {
        listener->onFeedback(message, success);
    });
}

void PlaybackNotifier::onStopped() {
    notify([](IPlaybackListener* listener) {
        listener->onStopped();
    });
}