#include "Playlist.h"
#include <random>
#include <algorithm>
#include <ranges>

Playlist::Playlist(MusicLibrary& musicLibrary) : music_library_(musicLibrary) {}

void Playlist::add(const Song& song) {
    songs_.push_back(song);
}

void Playlist::remove(const int index) {
    if (index < 0 || index >= songs_.size()) return;
    songs_[index].accept(music_library_);
    songs_.erase(songs_.begin() + index);

    if (index == current_song_) {
        current_song_ = -1;
    } else if (index < current_song_) {
        current_song_--;
    }
}

void Playlist::sort(SortingAlgorithm& criteria) {
    preserve();
    rearrange([&] { criteria.sort(songs_); });
}

void Playlist::reverse() {
    preserve();
    rearrange([this] { std::ranges::reverse(songs_); });
}

void Playlist::restore() {
    if (custom_order_.empty()) return;
    rearrange([this] { songs_ = custom_order_; custom_order_.clear(); });
}

void Playlist::preserve() {
    if (custom_order_.empty()) {
        custom_order_ = songs_;
    }
}

void Playlist::rearrange(const std::function<void()>& operation) {
    if (!hasSelected()) {
        operation();
        return;
    }
    const Song current = songs_[current_song_];
    operation();
    locate(current);
}

void Playlist::locate(const Song& target) {
    for (int i = 0; i < songs_.size(); i++) {
        if (songs_[i].isEqualTo(target)) {
            current_song_ = i;
            return;
        }
    }
    current_song_ = -1;
}

void Playlist::shuffle() {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    if (hasSelected()) {
        std::swap(songs_[0], songs_[current_song_]);
        std::shuffle(songs_.begin() + 1, songs_.end(), generator);
        current_song_ = 0;
    } else {
        std::ranges::shuffle(songs_, generator);
    }
}

void Playlist::clear() {
    songs_.clear();
    current_song_ = -1;
}

void Playlist::select(const int index, IPlaybackListener& listener) {
    if (index >= 0 && index < songs_.size()) {
        current_song_ = index;
        notify(listener);
    }
}

void Playlist::pick(const std::string& name, IPlaybackListener& listener) {
    for (int i = 0; i < songs_.size(); i++) {
        if (songs_[i].matches(name)) {
            select(i, listener);
            return;
        }
    }
}

void Playlist::advance(IPlaybackListener& listener) {
    if (hasNext()) {
        current_song_++;
        notify(listener);
    }
}

void Playlist::retreat(IPlaybackListener& listener) {
    if (current_song_ > 0) {
        current_song_--;
        notify(listener);
    }
}

void Playlist::notify(IPlaybackListener& listener) const {
    listener.onSelected(current_song_);
}

void Playlist::play(IPlaylistVisitor& player) const {
    if (hasSelected()) {
        songs_[current_song_].accept(player);
    }
}

void Playlist::accept(IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        song.accept(visitor);
    }
}

void Playlist::search(const std::string& query, IPlaylistVisitor& visitor) const {
    for (const Song& song : songs_) {
        if (song.matches(query)) {
            song.accept(visitor);
        }
    }
}

bool Playlist::hasNext() const {
    return current_song_ + 1 < static_cast<int>(songs_.size());
}

bool Playlist::hasSelected() const {
    return current_song_ >= 0 && current_song_ < static_cast<int>(songs_.size());
}