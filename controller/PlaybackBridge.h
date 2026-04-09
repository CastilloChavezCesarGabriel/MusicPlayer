#ifndef PLAYBACK_BRIDGE_H
#define PLAYBACK_BRIDGE_H

#include "model/events/IPlaybackEvent.h"
#include "../view/IPlaybackView.h"

class PlaybackBridge final : public IPlaybackEvent {
private:
    IPlaybackView& view_;

public:
    explicit PlaybackBridge(IPlaybackView& view);

    void onStart(const std::string& path) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
    void onStopped() override;
    void onEnabled(bool state) override;
    void onSelected(int index) override;
};

#endif //PLAYBACK_BRIDGE_H