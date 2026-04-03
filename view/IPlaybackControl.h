#ifndef I_PLAYBACK_CONTROL_H
#define I_PLAYBACK_CONTROL_H

class IPlaybackControl {
public:
    virtual ~IPlaybackControl() = default;
    virtual void onPlay(int index) = 0;
    virtual void onResume() = 0;
    virtual void onPause() = 0;
    virtual void onRepeat() = 0;
    virtual void onAdvance() = 0;
    virtual void onRetreat() = 0;
    virtual void onSkip() = 0;
    virtual void onEnd() = 0;
};

#endif //I_PLAYBACK_CONTROL_H