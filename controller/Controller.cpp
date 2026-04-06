#include "Controller.h"
#include "PlaylistRenderer.h"
#include "TitleDescending.h"
#include "CustomMode.h"
#include "../model/QuickSort.h"
#include "../model/DurationSort.h"
#include "../model/DateSort.h"

Controller::Controller(Model& model, IPlayerView& view)
        : model_(model), view_(view) {
    modes_.push_back(std::make_unique<SortMode>("Title \xe2\x96\xb2", new QuickSort()));
    modes_.push_back(std::make_unique<TitleDescending>());
    modes_.push_back(std::make_unique<SortMode>("Duration \xe2\x96\xb2", new DurationSort()));
    modes_.push_back(std::make_unique<SortMode>("Date Added \xe2\x96\xb2", new DateSort()));
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
    if (query.empty()) {
        view_.dismiss();
        return;
    }
    PlaylistRenderer renderer(view_);
    model_.search(query, renderer);
    renderer.suggest();
}

void Controller::onDrop(const std::vector<std::string>& paths) {
    for (const auto& path : paths) {
        model_.insert(path);
    }
}

void Controller::onAdjust(const int volume) {
    view_.adjust(volume);
}

void Controller::onEnd() {
    model_.end();
}

void Controller::refresh() const {
    PlaylistRenderer renderer(view_);
    model_.accept(renderer);
    renderer.render();
}