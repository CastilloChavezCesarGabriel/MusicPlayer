#ifndef QT_NOTIFICATION_H
#define QT_NOTIFICATION_H

#include "../../view/INotification.h"
#include <QWidget>

class QtNotification final : public INotification {
private:
    QWidget* parent_;

public:
    explicit QtNotification(QWidget* parent);
    void notify(const std::string& message, bool success) override;
};

#endif //QT_NOTIFICATION_H