#include "PlaybackBridge.h"

PlaybackBridge::PlaybackBridge(IPlaybackView& view) : view_(view) {}

void PlaybackBridge::onStart(const std::string& path) {
    view_.play(path);
}

void PlaybackBridge::onSchedule(const int delay) {
    view_.schedule(delay);
}

void PlaybackBridge::onCancel() {
    view_.cancel();
}

void PlaybackBridge::onRepeatChanged(const int mode) {
    view_.repeat(mode);
}

void PlaybackBridge::onFeedback(const std::string& message, const bool success) {
    view_.notify(message, success);
}

void PlaybackBridge::onStopped() {
    view_.stop();
}

void PlaybackBridge::onEnabled(const bool state) {
    view_.enable(state);
}

void PlaybackBridge::onSelected(int) {
    view_.enable(true);
}