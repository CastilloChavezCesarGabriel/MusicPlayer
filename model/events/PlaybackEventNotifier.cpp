#include "model/events/PlaybackEventNotifier.h"

void PlaybackEventNotifier::subscribe(IPlaybackEvent& observer) {
    observers_.push_back(&observer);
}

void PlaybackEventNotifier::notify(const std::function<void(IPlaybackEvent*)>& action) const {
    for (auto* observer : observers_) {
        action(observer);
    }
}

void PlaybackEventNotifier::onStart(const std::string& path) {
    notify([&](IPlaybackEvent* observer) {
        observer->onStart(path);
    });
}

void PlaybackEventNotifier::onChanged() {}

void PlaybackEventNotifier::onSelected(const int index) {
    notify([&](IPlaybackEvent* observer) {
        observer->onSelected(index);
    });
}

void PlaybackEventNotifier::onEnabled(const bool state) {
    notify([&](IPlaybackEvent* observer) {
        observer->onEnabled(state);
    });
}

void PlaybackEventNotifier::onReveal(bool) {}

void PlaybackEventNotifier::onSchedule(const int delay) {
    notify([&](IPlaybackEvent* observer) {
        observer->onSchedule(delay);
    });
}

void PlaybackEventNotifier::onCancel() {
    notify([](IPlaybackEvent* observer) {
        observer->onCancel();
    });
}

void PlaybackEventNotifier::onRepeatChanged(const int mode) {
    notify([&](IPlaybackEvent* observer) {
        observer->onRepeatChanged(mode);
    });
}

void PlaybackEventNotifier::onFeedback(const std::string& message, const bool success) {
    notify([&](IPlaybackEvent* observer) {
        observer->onFeedback(message, success);
    });
}

void PlaybackEventNotifier::onStopped() {
    notify([](IPlaybackEvent* observer) {
        observer->onStopped();
    });
}