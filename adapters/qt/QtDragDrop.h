#ifndef QT_DRAG_DROP_H
#define QT_DRAG_DROP_H

#include <QDropEvent>
#include <string>
#include <vector>

class QtDragDrop final {
public:
    static void accept(QDragEnterEvent* event);
    static std::vector<std::string> extract(const QDropEvent* event);
};

#endif //QT_DRAG_DROP_H