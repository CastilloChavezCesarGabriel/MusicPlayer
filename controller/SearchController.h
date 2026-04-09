#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include <string>

class SearchController {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;

public:
    SearchController(MusicPlayer& musicPlayer, IPlayerView& view);
    void search(const std::string& query) const;
};

#endif //SEARCH_CONTROLLER_H