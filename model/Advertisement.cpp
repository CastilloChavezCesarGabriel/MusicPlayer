#include "Advertisement.h"
#include "MusicLibrary.h"
#include <random>

Advertisement::Advertisement(const std::string& adsPath)
    : path_(adsPath) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::schedule() {
    return std::random_device{}() % 100 < 25;
}

bool Advertisement::interrupt(IPlaybackListener& listener) {
    if (ads_.empty()) return false;

    is_playing_ = true;

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, ads_.size() - 1);
    listener.onStart(ads_.at(distribution(engine)));
    return true;
}

bool Advertisement::conclude() {
    if (!is_playing_) return false;
    is_playing_ = false;
    return true;
}