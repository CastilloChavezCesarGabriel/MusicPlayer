#ifndef DISPLAY_DISPATCHER_H
#define DISPLAY_DISPATCHER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../view/IDisplayControl.h"
#include "SortController.h"
#include "SearchController.h"

class DisplayDispatcher final : public IDisplayControl {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;
    SortController sort_;
    SearchController search_;

public:
    DisplayDispatcher(MusicPlayer& musicPlayer, IPlayerView& view);

    void onSort() override;
    void onSearch(const std::string& query) override;
    void onPick(const std::string& name) override;
    void onAdjust(int volume) override;
};

#endif //DISPLAY_DISPATCHER_H
