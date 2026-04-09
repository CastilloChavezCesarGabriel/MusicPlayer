#ifndef I_PLAYBACK_EVENT_H
#define I_PLAYBACK_EVENT_H

#include <string>

class IPlaybackEvent {
public:
    virtual ~IPlaybackEvent() = default;
    virtual void onStart(const std::string& path) = 0;
    virtual void onSchedule(int delay) = 0;
    virtual void onCancel() = 0;
    virtual void onRepeatChanged(int mode) = 0;
    virtual void onFeedback(const std::string& message, bool success) = 0;
    virtual void onStopped() = 0;
    virtual void onEnabled(bool state) = 0;
    virtual void onSelected(int index) = 0;
};

#endif //I_PLAYBACK_EVENT_H