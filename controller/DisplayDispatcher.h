#ifndef DISPLAY_DISPATCHER_H
#define DISPLAY_DISPATCHER_H

#include "model/MusicPlayer.h"
#include "../view/IDisplayView.h"
#include "../view/IDisplayControl.h"
#include "SortController.h"
#include "SearchController.h"

class DisplayDispatcher final : public IDisplayControl {
private:
    MusicPlayer& music_player_;
    IDisplayView& view_;
    SortController sort_;
    SearchController search_;

public:
    DisplayDispatcher(MusicPlayer& musicPlayer, IDisplayView& view);

    void sort() override;
    void search(const std::string& query) override;
    void pick(const std::string& name) override;
};

#endif //DISPLAY_DISPATCHER_H
