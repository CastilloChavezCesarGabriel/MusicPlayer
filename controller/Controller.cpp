#include "Controller.h"
#include "PlaylistRenderer.h"

Controller::Controller(Model& model, IPlayerView& view)
        : model_(model), view_(view) {
    model_.subscribe(*this);
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

void Controller::onPlay(const int index) {
    model_.play(index);
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
    model_.repeat();
}

void Controller::onAdvance() {
    model_.advance();
}

void Controller::onRetreat() {
    model_.retreat();
}

void Controller::onAdd() {
    const std::string path = view_.browse();
    if (!path.empty()) {
        model_.insert(path);
    }
}

void Controller::onRemove(const int index) {
    if (view_.confirm("Are you sure you wanna delete this song?")) {
        model_.remove(index);
    }
}

void Controller::onShuffle() {
    model_.shuffle();
}

void Controller::onSkip() {
    model_.skip();
}

void Controller::onSort() {
    sort_mode_ = (sort_mode_ + 1) % 2;
    const bool byName = sort_mode_ == 0;
    model_.sort(byName);
    view_.sort(byName ? "Title \xe2\x96\xb2" : "# \xe2\x96\xb2");
}

void Controller::onSearch(const std::string& query) {
    refresh(query);
}

void Controller::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        model_.insert(path);
    }
}

void Controller::onAdjust(const int volume) {
    view_.adjust(volume / 100.0);
}

void Controller::onEnd() {
    model_.end();
}

void Controller::refresh(const std::string& query) const {
    PlaylistRenderer renderer(view_);
    if (query.empty()) {
        model_.accept(renderer);
    } else {
        model_.search(query, renderer);
    }
    renderer.render();
}
