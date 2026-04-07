#ifndef I_NOTIFICATION_H
#define I_NOTIFICATION_H

#include <string>

class INotification {
public:
    virtual ~INotification() = default;
    virtual void notify(const std::string& message, bool success) = 0;
};

#endif //I_NOTIFICATION_H