#ifndef QT_TOOLBAR_H
#define QT_TOOLBAR_H

#include <QWidget>
#include <QPushButton>
#include "IWidgetSetup.h"

class QtToolbar final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    QPushButton* add_button_;
    QPushButton* remove_button_;
    QPushButton* skip_button_;

public:
    explicit QtToolbar(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
    void reveal(bool visible) const;

signals:
    void addClicked();
    void removeClicked();
    void skipClicked();
};

#endif //QT_TOOLBAR_H