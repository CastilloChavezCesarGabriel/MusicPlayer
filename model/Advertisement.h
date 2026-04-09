#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include "IPlaybackListener.h"
#include "IDice.h"
#include <string>
#include <vector>

class Advertisement {
private:
    std::vector<std::string> ads_;
    std::string path_;
    IDice& dice_;
    bool is_playing_ = false;

    bool isScheduled() const;
    int randomize() const;

public:
    Advertisement(const std::string& adsPath, IDice& dice);

    void load();
    bool interrupt(IPlaybackListener& listener);
    bool conclude(IPlaybackListener& listener);
};

#endif //ADVERTISEMENT_H
