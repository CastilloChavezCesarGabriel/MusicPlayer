#ifndef PLAYBACK_DISPATCHER_H
#define PLAYBACK_DISPATCHER_H

#include "model/MusicPlayer.h"
#include "../view/IPlaybackView.h"
#include "../view/IPlaybackControl.h"

class PlaybackDispatcher final : public IPlaybackControl {
private:
    MusicPlayer& music_player_;
    IPlaybackView& view_;
    bool playing_ = false;

public:
    PlaybackDispatcher(MusicPlayer& musicPlayer, IPlaybackView& view);

    void play(int index) override;
    void toggle() override;
    void repeat() override;
    void advance() override;
    void retreat() override;
    void shuffle() override;
    void skip() override;
    void end() override;
    void adjust(int volume) override;
};

#endif //PLAYBACK_DISPATCHER_H