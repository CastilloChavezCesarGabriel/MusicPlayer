#ifndef I_PLAYBACK_CONTROL_H
#define I_PLAYBACK_CONTROL_H

class IPlaybackControl {
public:
    virtual ~IPlaybackControl() = default;
    virtual void play(int index) = 0;
    virtual void toggle() = 0;
    virtual void repeat() = 0;
    virtual void advance() = 0;
    virtual void retreat() = 0;
    virtual void shuffle() = 0;
    virtual void skip() = 0;
    virtual void end() = 0;
    virtual void adjust(int volume) = 0;
};

#endif //I_PLAYBACK_CONTROL_H