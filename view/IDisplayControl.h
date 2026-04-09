#ifndef I_DISPLAY_CONTROL_H
#define I_DISPLAY_CONTROL_H

#include <string>

class IDisplayControl {
public:
    virtual ~IDisplayControl() = default;
    virtual void sort() = 0;
    virtual void search(const std::string& query) = 0;
    virtual void pick(const std::string& name) = 0;
};

#endif //I_DISPLAY_CONTROL_H