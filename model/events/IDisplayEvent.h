#ifndef I_DISPLAY_EVENT_H
#define I_DISPLAY_EVENT_H

class IDisplayEvent {
public:
    virtual ~IDisplayEvent() = default;
    virtual void onChanged() = 0;
    virtual void onSelected(int index) = 0;
};

#endif //I_DISPLAY_EVENT_H