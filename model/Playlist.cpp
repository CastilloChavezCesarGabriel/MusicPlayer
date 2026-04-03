#include "Playlist.h"
#include <random>
#include <algorithm>

Playlist::Playlist(MusicLibrary& library) : library_(library) {}

void Playlist::add(const Song& song) {
    songs_.push_back(song);
}

void Playlist::remove(const int index) {
    if (index < 0 || index >= songs_.size()) return;
    songs_[index].accept(library_);
    songs_.erase(songs_.begin() + index);

    if (index == current_song_) {
        current_song_ = -1;
    } else if (index < current_song_) {
        current_song_--;
    }
}

void Playlist::sort(SortingAlgorithm& criteria) {
    criteria.sort(songs_);
}

void Playlist::shuffle() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::ranges::shuffle(songs_, generator);
    current_song_ = -1;
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
        if (song.match(query)) {
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