#ifndef I_DIALOG_H
#define I_DIALOG_H

#include <string>

class IDialog {
public:
    virtual ~IDialog() = default;
    virtual bool confirm(const std::string& message) = 0;
    virtual std::string browse() = 0;
};

#endif //I_DIALOG_H