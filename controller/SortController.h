#ifndef SORT_CONTROLLER_H
#define SORT_CONTROLLER_H

#include "SortMode.h"
#include "model/MusicPlayer.h"
#include "../view/IDisplayView.h"
#include <vector>
#include <memory>

class SortController {
private:
    MusicPlayer& music_player_;
    IDisplayView& view_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int index_ = -1;

public:
    SortController(MusicPlayer& musicPlayer, IDisplayView& view);
    void cycle();
};

#endif //SORT_CONTROLLER_H
