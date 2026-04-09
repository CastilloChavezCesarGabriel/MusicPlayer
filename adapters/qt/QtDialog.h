#ifndef QT_DIALOG_H
#define QT_DIALOG_H

#include <QWidget>
#include <string>

class QtDialog final {
private:
    QWidget* parent_;

public:
    explicit QtDialog(QWidget* parent);
    bool confirm(const std::string& message) const;
    std::string browse() const;
};

#endif //QT_DIALOG_H