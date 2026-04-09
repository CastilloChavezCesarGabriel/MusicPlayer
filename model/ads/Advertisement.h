#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "model/events/IPlaybackListener.h"
#include "model/ads/IAdPolicy.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    std::string path_;
    IAdPolicy& policy_;
    bool is_playing_ = false;

public:
    Advertisement(const std::string& adsPath, IAdPolicy& policy);

    void load();
    bool interrupt(IPlaybackListener& listener);
    bool conclude(IPlaybackListener& listener);
};

#endif //ADVERTISEMENT_H