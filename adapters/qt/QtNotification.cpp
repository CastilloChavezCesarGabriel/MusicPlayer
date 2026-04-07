#include "QtNotification.h"
#include <QMessageBox>

QtNotification::QtNotification(QWidget* parent) : parent_(parent) {}

void QtNotification::notify(const std::string& message, const bool success) {
    QMessageBox::information(parent_, success ? "Success" : "Oops",
                             QString::fromStdString(message));
}