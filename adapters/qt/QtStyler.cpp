#include "QtStyler.h"
#include <QFile>

void QtStyler::apply(QApplication& app, const std::string& path) {
    QFile stylesheet(QString::fromStdString(path));
    if (stylesheet.open(QFile::ReadOnly)) {
        app.setStyleSheet(stylesheet.readAll());
        stylesheet.close();
    }
}