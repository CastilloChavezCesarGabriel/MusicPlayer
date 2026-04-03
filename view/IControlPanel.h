#ifndef I_CONTROL_PANEL_H
#define I_CONTROL_PANEL_H

class IControlPanel {
public:
    virtual ~IControlPanel() = default;
    virtual void enable(bool state) = 0;
    virtual void reveal(bool visible) = 0;
};

#endif //I_CONTROL_PANEL_H