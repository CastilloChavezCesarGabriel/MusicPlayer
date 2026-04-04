#include "Model.h"
#include "Channel.h"
#include "ShellSort.h"
#include "QuickSort.h"

Model::Model(const std::string& basePath)
    : music_library_(basePath + "/music"),
      playlist_(music_library_),
      advertisement_(basePath + "/announcements") {

    for (const Song& song : music_library_.load()) {
        playlist_.add(song);
    }
    playlist_.shuffle();
    advertisement_.load();
}

void Model::subscribe(IPlaybackListener& listener) {
    notifier_.add(listener);
}

void Model::play(const int index) {
    playlist_.select(index, notifier_);

    if (!advertisement_.interrupt(notifier_)) {
        broadcast();
    }
}

void Model::advance() {
    if (playlist_.hasNext()) {
        playlist_.advance(notifier_);
        broadcast();
    }
}

void Model::retreat() {
    playlist_.retreat(notifier_);
    broadcast();
}

void Model::end() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
        return;
    }

    if (repeat_mode_ == 1) {
        broadcast();
        return;
    }

    if (playlist_.hasNext()) {
        advance();
    } else if (repeat_mode_ == 2) {
        playlist_.select(0, notifier_);
        broadcast();
    }
}

void Model::skip() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
    }
}

void Model::broadcast() {
    Channel channel(notifier_);
    playlist_.play(channel);
}

void Model::refresh() {
    notifier_.onChanged();
}

void Model::repeat() {
    repeat_mode_ = (repeat_mode_ + 1) % 3;
    notifier_.onRepeatChanged(repeat_mode_);
}

void Model::insert(const std::string& filePath) {
    const std::string reason = music_library_.validate(filePath);
    if (!reason.empty()) {
        notifier_.onFeedback(reason, false);
        return;
    }

    playlist_.add(music_library_.import(filePath));
    refresh();
    notifier_.onFeedback("Song added successfully!", true);
}

void Model::remove(const int index) {
    playlist_.remove(index);
    refresh();
}

void Model::shuffle() {
    playlist_.shuffle();
    refresh();
}

void Model::sort(const bool byName) {
    if (byName) {
        QuickSort byTitle;
        playlist_.sort(byTitle);
    } else {
        ShellSort byNumber;
        playlist_.sort(byNumber);
    }
    refresh();
}

void Model::accept(IPlaylistVisitor& visitor) const {
    playlist_.accept(visitor);
}

void Model::search(const std::string& query, IPlaylistVisitor& visitor) const {
    playlist_.search(query, visitor);
}