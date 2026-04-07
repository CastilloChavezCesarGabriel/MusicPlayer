#ifndef PLAYBACK_NOTIFIER_H
#define PLAYBACK_NOTIFIER_H

#include "IPlaybackListener.h"
#include <vector>
#include <string>
#include <functional>

class PlaybackNotifier final : public IPlaybackListener {
private:
    std::vector<IPlaybackListener*> listeners_;

    void notify(const std::function<void(IPlaybackListener*)>& action) const;

public:
    void add(IPlaybackListener& listener);
    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onSchedule(int delay) override;
    void onCancel() override;
    void onRepeatChanged(int mode) override;
    void onFeedback(const std::string& message, bool success) override;
};

#endif //PLAYBACK_NOTIFIER_H