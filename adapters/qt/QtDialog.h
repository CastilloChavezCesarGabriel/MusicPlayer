#ifndef QT_DIALOG_H
#define QT_DIALOG_H

#include "../../view/IDialog.h"
#include <QWidget>

class QtDialog final : public IDialog {
private:
    QWidget* parent_;

public:
    explicit QtDialog(QWidget* parent);
    bool confirm(const std::string& message) override;
    std::string browse() override;
};

#endif //QT_DIALOG_H