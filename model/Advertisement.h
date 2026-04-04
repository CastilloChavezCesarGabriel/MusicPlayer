#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "IPlaybackListener.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    std::string path_;
    bool is_playing_ = false;

public:
    explicit Advertisement(const std::string& adsPath);

    void load();
    bool interrupt(IPlaybackListener& listener);
    bool conclude(IPlaybackListener& listener);

private:
    static bool isScheduled();
    static int randomize();
};

#endif //ADVERTISEMENT_H