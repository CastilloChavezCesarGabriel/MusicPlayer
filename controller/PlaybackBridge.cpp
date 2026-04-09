#include "PlaybackBridge.h"
#include "PlaylistRenderer.h"

PlaybackBridge::PlaybackBridge(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {
    music_player_.subscribe(*this);
    refresh();
}

void PlaybackBridge::onStart(const std::string& path) {
    view_.play(path);
}

void PlaybackBridge::onChanged() {
    refresh();
}

void PlaybackBridge::onSelected(const int index) {
    view_.highlight(index);
    view_.enable(true);
}

void PlaybackBridge::onEnabled(const bool state) {
    view_.enable(state);
}

void PlaybackBridge::onReveal(const bool visible) {
    view_.reveal(visible);
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

void PlaybackBridge::refresh() const {
    PlaylistRenderer renderer(view_);
    music_player_.accept(renderer);
    renderer.render();
}
