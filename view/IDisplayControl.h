#ifndef I_DISPLAY_CONTROL_H
#define I_DISPLAY_CONTROL_H

#include <string>

class IDisplayControl {
public:
    virtual ~IDisplayControl() = default;
    virtual void onSort() = 0;
    virtual void onSearch(const std::string& query) = 0;
    virtual void onPick(const std::string& name) = 0;
    virtual void onAdjust(int volume) = 0;
};

#endif //I_DISPLAY_CONTROL_H