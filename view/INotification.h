#ifndef I_NOTIFICATION_H
#define I_NOTIFICATION_H

#include <string>

class INotification {
public:
    virtual ~INotification() = default;
    virtual void notify(const std::string& message, bool success) = 0;
    virtual bool confirm(const std::string& message) = 0;
    virtual std::string browse() = 0;
};

#endif //I_NOTIFICATION_H