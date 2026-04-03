#include "MockPlaybackListener.h"
#include <algorithm>

void MockPlaybackListener::onStart(const std::string& path) {
    starts_.push_back(path);
}

void MockPlaybackListener::onChanged() {
    changes_++;
}

void MockPlaybackListener::onSelected(const int index) {
    selections_.push_back(index);
}

void MockPlaybackListener::onEnabled(bool) {
    enables_++;
}

void MockPlaybackListener::onReveal(bool) {
    reveals_++;
}

void MockPlaybackListener::onFeedback(const std::string& message, bool) {
    feedbacks_.push_back(message);
}

bool MockPlaybackListener::wasStarted() const {
    return !starts_.empty();
}

bool MockPlaybackListener::wasStartedWith(const std::string& path) const {
    return std::ranges::find(starts_, path) != starts_.end();
}

bool MockPlaybackListener::wasChanged() const {
    return changes_ > 0;
}

bool MockPlaybackListener::wasChangedTimes(const int expected) const {
    return changes_ == expected;
}

bool MockPlaybackListener::wasSelected() const {
    return !selections_.empty();
}

bool MockPlaybackListener::wasSelectedWith(const int index) const {
    return std::ranges::find(selections_, index) != selections_.end();
}

bool MockPlaybackListener::wasEnabled() const {
    return enables_ > 0;
}

bool MockPlaybackListener::wasRevealed() const {
    return reveals_ > 0;
}

bool MockPlaybackListener::wasFeedback(const std::string& message) const {
    return std::ranges::find(feedbacks_, message) != feedbacks_.end();
}
