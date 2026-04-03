#ifndef QT_TOOLBAR_H
#define QT_TOOLBAR_H

#include <QWidget>
#include <QPushButton>

class QtToolbar final : public QWidget {
    Q_OBJECT
private:
    QPushButton* add_button_;
    QPushButton* remove_button_;
    QPushButton* skip_button_;
    QPushButton* sort_by_number_button;
    QPushButton* sort_by_name_button;

    void setup();
    void wire();

public:
    explicit QtToolbar(QWidget* parent = nullptr);
    void enable(bool state) const;
    void reveal(bool visible) const;

signals:
    void addClicked();
    void removeClicked();
    void skipClicked();
    void sortByNumberClicked();
    void sortByNameClicked();
};

#endif //QT_TOOLBAR_H