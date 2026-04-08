#include "MusicPlayer.h"
#include "Channel.h"

MusicPlayer::MusicPlayer(const std::string& basePath)
    : music_library_(basePath + "/music"),
      playlist_(music_library_),
      advertisement_(basePath + "/announcements"),
      repeat_mode_(playlist_, notifier_) {

    for (const Song& song : music_library_.load()) {
        playlist_.add(song);
    }
    playlist_.shuffle();
    advertisement_.load();
}

void MusicPlayer::subscribe(IPlaybackListener& listener) {
    notifier_.add(listener);
}

void MusicPlayer::play(const int index) {
    playlist_.select(index, notifier_);

    if (!advertisement_.interrupt(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::pick(const std::string& name) {
    playlist_.pick(name, notifier_);

    if (!advertisement_.interrupt(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::advance() {
    if (playlist_.hasNext()) {
        playlist_.advance(notifier_);
        broadcast();
    }
}

void MusicPlayer::retreat() {
    playlist_.retreat(notifier_);
    broadcast();
}

void MusicPlayer::end() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
        return;
    }
    repeat_mode_.apply();
    broadcast();
}

void MusicPlayer::skip() {
    if (advertisement_.conclude(notifier_)) {
        broadcast();
    }
}

void MusicPlayer::broadcast() {
    Channel channel(notifier_);
    playlist_.play(channel);
}

void MusicPlayer::refresh() {
    notifier_.onChanged();
}

void MusicPlayer::repeat() {
    repeat_mode_.advance();
}

void MusicPlayer::insert(const std::string& filePath) {
    const std::string reason = music_library_.validate(filePath);
    if (!reason.empty()) {
        notifier_.onFeedback(reason, false);
        return;
    }

    playlist_.add(music_library_.import(filePath));
    refresh();
    notifier_.onFeedback("Song added successfully!", true);
}

void MusicPlayer::remove(const int index) {
    playlist_.remove(index);
    refresh();
}

void MusicPlayer::shuffle() {
    playlist_.shuffle();
    refresh();
}

void MusicPlayer::sort(SortingAlgorithm& criteria) {
    playlist_.sort(criteria);
    refresh();
}

void MusicPlayer::reverse() {
    playlist_.reverse();
    refresh();
}

void MusicPlayer::restore() {
    playlist_.restore();
    refresh();
}

void MusicPlayer::accept(IPlaylistVisitor& visitor) const {
    playlist_.accept(visitor);
}

void MusicPlayer::search(const std::string& query, IPlaylistVisitor& visitor) const {
    playlist_.search(query, visitor);
}