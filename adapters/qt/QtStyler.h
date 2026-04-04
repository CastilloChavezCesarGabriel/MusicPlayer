#ifndef QT_STYLER_H
#define QT_STYLER_H

#include <QApplication>
#include <string>

class QtStyler {
public:
    static void apply(QApplication& app, const std::string& path);
};

#endif //QT_STYLER_H