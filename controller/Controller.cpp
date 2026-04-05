#include "Controller.h"
#include "PlaylistRenderer.h"
#include "TitleAscending.h"
#include "TitleDescending.h"
#include "DurationMode.h"
#include "DateMode.h"
#include "CustomMode.h"

Controller::Controller(Model& model, IPlayerView& view)
        : model_(model), view_(view) {
    modes_.push_back(std::make_unique<TitleAscending>());
    modes_.push_back(std::make_unique<TitleDescending>());
    modes_.push_back(std::make_unique<DurationMode>());
    modes_.push_back(std::make_unique<DateMode>());
    modes_.push_back(std::make_unique<CustomMode>());
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
    sort_index_ = (sort_index_ + 1) % static_cast<int>(modes_.size());
    modes_[sort_index_]->apply(model_);
    modes_[sort_index_]->display(view_);
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
