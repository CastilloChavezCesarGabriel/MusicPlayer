#include "model/ads/Advertisement.h"
#include "model/library/MusicLibrary.h"

Advertisement::Advertisement(const std::string& adsPath, IAdPolicy& policy)
    : path_(adsPath), policy_(policy) {
}

void Advertisement::load() {
    ads_ = MusicLibrary::scan(path_);
}

bool Advertisement::interrupt(IPlaybackListener& listener) {
    if (ads_.empty() || !policy_.decide()) return false;

    is_playing_ = true;
    listener.onEnabled(false);
    listener.onSchedule(policy_.clock());
    listener.onStart(policy_.pick(ads_));
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
