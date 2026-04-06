#ifndef QT_SEARCH_OVERLAY_H
#define QT_SEARCH_OVERLAY_H

#include <QListWidget>
#include <QWidget>
#include <string>
#include <vector>

class QtSearchOverlay final : public QWidget {
    Q_OBJECT
private:
    QListWidget* results_;

    void setup();
    void align();

public:
    explicit QtSearchOverlay(QWidget* parent = nullptr);
    void display(const std::vector<std::string>& names);
    void clear();

signals:
    void selectRequested(const std::string& name);
};

#endif //QT_SEARCH_OVERLAY_H
