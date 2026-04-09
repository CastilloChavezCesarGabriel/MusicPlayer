#ifndef MOCK_PLAYBACK_LISTENER_H
#define MOCK_PLAYBACK_LISTENER_H

#include "../model/IPlaybackListener.h"
#include <string>
#include <vector>

class MockPlaybackListener final : public IPlaybackListener {
private:
    std::vector<std::string> starts_;
    std::vector<int> selections_;
    std::vector<std::string> feedbacks_;
    int changes_ = 0;
    int enables_ = 0;
    int reveals_ = 0;
    int cancels_ = 0;
    int stops_ = 0;

public:
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

    bool wasStarted() const;
    bool wasStartedWith(const std::string& path) const;
    bool wasChanged() const;
    bool wasChangedTimes(int expected) const;
    bool wasSelected() const;
    bool wasSelectedWith(int index) const;
    bool wasEnabled() const;
    bool wasRevealed() const;
    bool wasCancelled() const;
    bool wasFeedback(const std::string& message) const;
    bool wasStopped() const;
};

#endif //MOCK_PLAYBACK_LISTENER_H