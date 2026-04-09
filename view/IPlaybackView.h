#ifndef I_PLAYBACK_VIEW_H
#define I_PLAYBACK_VIEW_H

#include <string>

class IPlaybackView {
public:
    virtual ~IPlaybackView() = default;
    virtual void play(const std::string& path) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void stop() = 0;
    virtual void adjust(int volume) = 0;
    virtual void enable(bool state) = 0;
    virtual void schedule(int delay) = 0;
    virtual void cancel() = 0;
    virtual void repeat(int mode) = 0;
    virtual void notify(const std::string& message, bool success) = 0;
};

#endif //I_PLAYBACK_VIEW_H