#ifndef QT_LAYOUT_UTIL_H
#define QT_LAYOUT_UTIL_H

#include <QLayout>

class QtLayoutUtil final {
public:
    static void flatten(QLayout* layout);
    static void center(QLayout* layout);
};

#endif //QT_LAYOUT_UTIL_H
