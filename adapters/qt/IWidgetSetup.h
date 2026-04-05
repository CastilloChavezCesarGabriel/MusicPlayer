#ifndef I_WIDGET_SETUP_H
#define I_WIDGET_SETUP_H

class IWidgetSetup {
public:
    virtual ~IWidgetSetup() = default;
    virtual void setup() = 0;
    virtual void wire() = 0;
};

#endif //I_WIDGET_SETUP_H