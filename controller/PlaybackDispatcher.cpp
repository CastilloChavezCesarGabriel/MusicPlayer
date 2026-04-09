#include "PlaybackDispatcher.h"

PlaybackDispatcher::PlaybackDispatcher(MusicPlayer& musicPlayer, IPlaybackView& view)
    : music_player_(musicPlayer), view_(view) {}

void PlaybackDispatcher::play(const int index) {
    music_player_.play(index);
}

void PlaybackDispatcher::toggle() {
    if (playing_) {
        view_.pause();
    } else {
        view_.resume();
    }
    playing_ = !playing_;
}

void PlaybackDispatcher::repeat() {
    music_player_.repeat();
}

void PlaybackDispatcher::advance() {
    music_player_.advance();
}

void PlaybackDispatcher::retreat() {
    music_player_.retreat();
}

void PlaybackDispatcher::shuffle() {
    music_player_.shuffle();
}

void PlaybackDispatcher::skip() {
    music_player_.skip();
}

void PlaybackDispatcher::end() {
    music_player_.end();
}

void PlaybackDispatcher::adjust(const int volume) {
    view_.adjust(volume);
}