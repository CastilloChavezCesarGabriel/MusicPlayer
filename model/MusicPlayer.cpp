#include "model/MusicPlayer.h"
#include "model/playback/Channel.h"
#include "model/repeat/NoRepeatMode.h"
#include "model/repeat/RepeatOneMode.h"
#include "model/repeat/RepeatAllMode.h"

MusicPlayer::MusicPlayer(const std::string& basePath, IAdPolicy& adPolicy) : music_library_(basePath + "/music"),
      playlist_(music_library_), advertisement_(basePath + "/announcements", adPolicy),
      repeat_mode_(playlist_, notifier_) {

    repeat_mode_.add(std::make_unique<NoRepeatMode>());
    repeat_mode_.add(std::make_unique<RepeatOneMode>());
    repeat_mode_.add(std::make_unique<RepeatAllMode>());

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

    if (repeat_mode_.apply()) {
        broadcast();
    } else {
        notifier_.onStopped();
    }
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
    const std::string reason = music_library_.insert(filePath, playlist_);
    if (!reason.empty()) {
        notifier_.onFeedback(reason, false);
        return;
    }
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

void MusicPlayer::sort(ISortingAlgorithm& criteria) {
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