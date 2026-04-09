#include "model/events/LibraryEventNotifier.h"

void LibraryEventNotifier::subscribe(ILibraryEvent& observer) {
    observers_.push_back(&observer);
}

void LibraryEventNotifier::notify(const std::function<void(ILibraryEvent*)>& action) const {
    for (auto* observer : observers_) {
        action(observer);
    }
}

void LibraryEventNotifier::onStart(const std::string&) {}
void LibraryEventNotifier::onChanged() {}

void LibraryEventNotifier::onSelected(const int index) {
    notify([&](ILibraryEvent* observer) {
        observer->onSelected(index);
    });
}

void LibraryEventNotifier::onEnabled(const bool state) {
    notify([&](ILibraryEvent* observer) {
        observer->onEnabled(state);
    });
}

void LibraryEventNotifier::onReveal(const bool visible) {
    notify([&](ILibraryEvent* observer) {
        observer->onReveal(visible);
    });
}

void LibraryEventNotifier::onSchedule(int) {}
void LibraryEventNotifier::onCancel() {}
void LibraryEventNotifier::onRepeatChanged(int) {}
void LibraryEventNotifier::onFeedback(const std::string&, bool) {}
void LibraryEventNotifier::onStopped() {}