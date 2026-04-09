#ifndef PLAYBACK_BRIDGE_H
#define PLAYBACK_BRIDGE_H

#include "../model/IPlaybackListener.h"
#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"

class PlaybackBridge final : public IPlaybackListener {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;

    void refresh() const;

public:
    PlaybackBridge(MusicPlayer& musicPlayer, IPlayerView& view);

    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
    void onStopped() override;
};

#endif //PLAYBACK_BRIDGE_H
