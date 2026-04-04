#ifndef I_CONTROL_PANEL_H
#define I_CONTROL_PANEL_H
#include <string>

class IControlPanel {
public:
    virtual ~IControlPanel() = default;
    virtual void enable(bool state) = 0;
    virtual void reveal(bool visible) = 0;
    virtual void schedule(int delay) = 0;
    virtual void cancel() = 0;
    virtual void repeat(int mode) = 0;
    virtual void sort(const std::string& label) = 0;
};

#endif //I_CONTROL_PANEL_H