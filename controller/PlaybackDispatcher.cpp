#include "PlaybackDispatcher.h"

PlaybackDispatcher::PlaybackDispatcher(MusicPlayer& musicPlayer, IPlayerView& view)
    : music_player_(musicPlayer), view_(view) {}

void PlaybackDispatcher::onPlay(const int index) {
    music_player_.play(index);
}

void PlaybackDispatcher::onToggle() {
    if (playing_) {
        view_.pause();
    } else {
        view_.resume();
    }
    playing_ = !playing_;
}

void PlaybackDispatcher::onRepeat() {
    music_player_.repeat();
}

void PlaybackDispatcher::onAdvance() {
    music_player_.advance();
}

void PlaybackDispatcher::onRetreat() {
    music_player_.retreat();
}

void PlaybackDispatcher::onShuffle() {
    music_player_.shuffle();
}

void PlaybackDispatcher::onSkip() {
    music_player_.skip();
}

void PlaybackDispatcher::onEnd() {
    music_player_.end();
}
