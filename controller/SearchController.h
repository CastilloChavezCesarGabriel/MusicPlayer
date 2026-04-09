#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "model/MusicPlayer.h"
#include "../view/IDisplayView.h"
#include <string>

class SearchController {
private:
    MusicPlayer& music_player_;
    IDisplayView& view_;

public:
    SearchController(MusicPlayer& musicPlayer, IDisplayView& view);
    void search(const std::string& query) const;
};

#endif //SEARCH_CONTROLLER_H
