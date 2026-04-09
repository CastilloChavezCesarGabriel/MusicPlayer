#ifndef LIBRARY_EVENT_NOTIFIER_H
#define LIBRARY_EVENT_NOTIFIER_H

#include "model/events/IPlaybackListener.h"
#include "model/events/ILibraryEvent.h"
#include <vector>
#include <functional>

class LibraryEventNotifier final : public IPlaybackListener {
private:
    std::vector<ILibraryEvent*> observers_;

    void notify(const std::function<void(ILibraryEvent*)>& action) const;

public:
    void subscribe(ILibraryEvent& observer);

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

#endif //LIBRARY_EVENT_NOTIFIER_H