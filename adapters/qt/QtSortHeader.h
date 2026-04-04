#ifndef QT_SORT_HEADER_H
#define QT_SORT_HEADER_H

#include <QWidget>
#include <QPushButton>
#include <string>

class QtSortHeader final : public QWidget {
    Q_OBJECT
private:
    QPushButton* header_;

public:
    explicit QtSortHeader(QWidget* parent = nullptr);
    void display(const std::string& text) const;

signals:
    void clickRequested();
};

#endif //QT_SORT_HEADER_H
