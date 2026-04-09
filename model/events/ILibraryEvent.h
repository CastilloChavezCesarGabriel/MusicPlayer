#ifndef I_LIBRARY_EVENT_H
#define I_LIBRARY_EVENT_H

class ILibraryEvent {
public:
    virtual ~ILibraryEvent() = default;
    virtual void onReveal(bool visible) = 0;
    virtual void onEnabled(bool state) = 0;
    virtual void onSelected(int index) = 0;
};

#endif //I_LIBRARY_EVENT_H