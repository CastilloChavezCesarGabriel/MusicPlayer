#include "Controller.h"
#include "PlaylistRenderer.h"

Controller::Controller(Model& model, IPlayerView& view)
        : model_(model), view_(view) {
    model_.add(*this);
    view_.add(this);
    refresh();
}

void Controller::onStart(const std::string& path) {
    view_.play(path);
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

void Controller::onFeedback(const std::string& message, const bool success) {
    view_.notify(message, success);
}

void Controller::onPlay(const int index) {
    model_.play(index);
}

void Controller::onResume() {
    view_.resume();
}

void Controller::onPause() {
    view_.pause();
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

void Controller::onSkip() {
    model_.skip();
}

void Controller::onSort(const bool byName) {
    model_.sort(byName);
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
