#ifndef PLAYBACK_DISPATCHER_H
#define PLAYBACK_DISPATCHER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../view/IPlaybackControl.h"

class PlaybackDispatcher final : public IPlaybackControl {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;
    bool playing_ = false;

public:
    PlaybackDispatcher(MusicPlayer& musicPlayer, IPlayerView& view);

    void onPlay(int index) override;
    void onToggle() override;
    void onRepeat() override;
    void onAdvance() override;
    void onRetreat() override;
    void onShuffle() override;
    void onSkip() override;
    void onEnd() override;
};

#endif //PLAYBACK_DISPATCHER_H
