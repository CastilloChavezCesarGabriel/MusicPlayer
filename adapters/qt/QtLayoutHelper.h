#ifndef QT_LAYOUT_HELPER_H
#define QT_LAYOUT_HELPER_H

#include <QLayout>

class QtLayoutHelper final {
public:
    static void flatten(QLayout* layout);
    static void center(QLayout* layout);
};

#endif //QT_LAYOUT_HELPER_H
