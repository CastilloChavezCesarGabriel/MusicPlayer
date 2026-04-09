#ifndef DISPLAY_BRIDGE_H
#define DISPLAY_BRIDGE_H

#include "model/events/IDisplayEvent.h"
#include "../view/IDisplayView.h"
#include "model/MusicPlayer.h"

class DisplayBridge final : public IDisplayEvent {
private:
    MusicPlayer& music_player_;
    IDisplayView& view_;

    void render() const;

public:
    DisplayBridge(MusicPlayer& musicPlayer, IDisplayView& view);

    void onChanged() override;
    void onSelected(int index) override;
};

#endif //DISPLAY_BRIDGE_H
