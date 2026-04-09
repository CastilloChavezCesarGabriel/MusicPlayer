#ifndef DISPLAY_EVENT_NOTIFIER_H
#define DISPLAY_EVENT_NOTIFIER_H

#include "model/events/IPlaybackListener.h"
#include "model/events/IDisplayEvent.h"
#include <vector>
#include <functional>

class DisplayEventNotifier final : public IPlaybackListener {
private:
    std::vector<IDisplayEvent*> observers_;

    void notify(const std::function<void(IDisplayEvent*)>& action) const;

public:
    void subscribe(IDisplayEvent& observer);

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

#endif //DISPLAY_EVENT_NOTIFIER_H