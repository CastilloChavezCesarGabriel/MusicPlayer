#include "Advertisement.h"
#include "MusicLibrary.h"
#include <random>

Advertisement::Advertisement(const std::string& adsPath)
    : path_(adsPath) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::isScheduled() {
    return std::random_device{}() % 100 < 25;
}

int Advertisement::randomize() {
    return (std::random_device{}() % 6 + 5) * 1000;
}

bool Advertisement::interrupt(IPlaybackListener& listener) {
    if (ads_.empty() || !isScheduled()) return false;

    is_playing_ = true;
    listener.onEnabled(false);
    listener.onSchedule(randomize());

    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, ads_.size() - 1);
    listener.onStart(ads_.at(distribution(engine)));
    return true;
}

bool Advertisement::conclude(IPlaybackListener& listener) {
    if (!is_playing_) return false;
    is_playing_ = false;
    listener.onCancel();
    listener.onReveal(false);
    listener.onEnabled(true);
    return true;
}