#include "Controller.h"
#include "PlaylistRenderer.h"

Controller::Controller(MusicPlayer& musicPlayer, IPlayerView& view) : music_player_(musicPlayer), view_(view),
          sort_(musicPlayer, view), search_(musicPlayer, view) {
    music_player_.subscribe(*this);
    view_.add(this);
    refresh();
}

void Controller::onStart(const std::string& path) {
    view_.play(path);
    playing_ = true;
}

void Controller::onChanged() {
    refresh();
}

void Controller::onSelected(const int index) {
    view_.highlight(index);
    view_.enable(true);
}

void Controller::onEnabled(const bool state) {
    view_.enable(state);
}

void Controller::onReveal(const bool visible) {
    view_.reveal(visible);
}

void Controller::onSchedule(const int delay) {
    view_.schedule(delay);
}

void Controller::onCancel() {
    view_.cancel();
}

void Controller::onRepeatChanged(const int mode) {
    view_.repeat(mode);
}

void Controller::onFeedback(const std::string& message, const bool success) {
    view_.notify(message, success);
}

void Controller::onStopped() {
    view_.enable(false);
    view_.pause();
    view_.highlight(-1);
    playing_ = false;
}

void Controller::onPlay(const int index) {
    music_player_.play(index);
}

void Controller::onToggle() {
    if (playing_) {
        view_.pause();
    } else {
        view_.resume();
    }
    playing_ = !playing_;
}

void Controller::onRepeat() {
    music_player_.repeat();
}

void Controller::onAdvance() {
    music_player_.advance();
}

void Controller::onRetreat() {
    music_player_.retreat();
}

void Controller::onAdd() {
    const std::string path = view_.browse();
    if (!path.empty()) {
        music_player_.insert(path);
    }
}

void Controller::onRemove(const int index) {
    if (view_.confirm("Are you sure you wanna delete this song?")) {
        music_player_.remove(index);
    }
}

void Controller::onShuffle() {
    music_player_.shuffle();
}

void Controller::onSkip() {
    music_player_.skip();
}

void Controller::onSort() {
    sort_.cycle();
}

void Controller::onSearch(const std::string& query) {
    search_.search(query);
}

void Controller::onPick(const std::string& name) {
    music_player_.pick(name);
    view_.dismiss();
}

void Controller::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        music_player_.insert(path);
    }
}

void Controller::onAdjust(const int volume) {
    view_.adjust(volume);
}

void Controller::onEnd() {
    music_player_.end();
}

void Controller::refresh() const {
    PlaylistRenderer renderer(view_);
    music_player_.accept(renderer);
    renderer.render();
}