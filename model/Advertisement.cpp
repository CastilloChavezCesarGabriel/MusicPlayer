#include "Advertisement.h"
#include "MusicLibrary.h"

Advertisement::Advertisement(const std::string& adsPath, IDice& dice)
    : path_(adsPath), dice_(dice) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::isScheduled() const {
    return dice_.roll(100) <= 25;
}

int Advertisement::randomize() const {
    return (dice_.roll(6) + 4) * 1000;
}

bool Advertisement::interrupt(IPlaybackListener& listener) {
    if (ads_.empty() || !isScheduled()) return false;

    is_playing_ = true;
    listener.onEnabled(false);
    listener.onSchedule(randomize());

    const int index = dice_.roll(static_cast<int>(ads_.size())) - 1;
    listener.onStart(ads_.at(index));
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