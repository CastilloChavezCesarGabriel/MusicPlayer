#include "model/events/DisplayEventNotifier.h"

void DisplayEventNotifier::subscribe(IDisplayEvent& observer) {
    observers_.push_back(&observer);
}

void DisplayEventNotifier::notify(const std::function<void(IDisplayEvent*)>& action) const {
    for (auto* observer : observers_) {
        action(observer);
    }
}

void DisplayEventNotifier::onStart(const std::string&) {}

void DisplayEventNotifier::onChanged() {
    notify([](IDisplayEvent* observer) {
        observer->onChanged();
    });
}

void DisplayEventNotifier::onSelected(const int index) {
    notify([&](IDisplayEvent* observer) {
        observer->onSelected(index);
    });
}

void DisplayEventNotifier::onEnabled(bool) {}
void DisplayEventNotifier::onReveal(bool) {}
void DisplayEventNotifier::onSchedule(int) {}
void DisplayEventNotifier::onCancel() {}
void DisplayEventNotifier::onRepeatChanged(int) {}
void DisplayEventNotifier::onFeedback(const std::string&, bool) {}
void DisplayEventNotifier::onStopped() {}