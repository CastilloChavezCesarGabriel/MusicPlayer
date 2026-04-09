#ifndef QT_NOTIFICATION_H
#define QT_NOTIFICATION_H

#include <QWidget>
#include <string>

class QtNotification final {
private:
    QWidget* parent_;

public:
    explicit QtNotification(QWidget* parent);
    void notify(const std::string& message, bool success);
};

#endif //QT_NOTIFICATION_H
