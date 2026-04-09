#ifndef PLAYBACK_EVENT_NOTIFIER_H
#define PLAYBACK_EVENT_NOTIFIER_H

#include "model/events/IPlaybackListener.h"
#include "model/events/IPlaybackEvent.h"
#include <vector>
#include <functional>

class PlaybackEventNotifier final : public IPlaybackListener {
private:
    std::vector<IPlaybackEvent*> observers_;

    void notify(const std::function<void(IPlaybackEvent*)>& action) const;

public:
    void subscribe(IPlaybackEvent& observer);

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

#endif //PLAYBACK_EVENT_NOTIFIER_H