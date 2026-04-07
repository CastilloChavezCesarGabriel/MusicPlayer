#include "QtLayoutUtil.h"

void QtLayoutUtil::flatten(QLayout* layout) {
    layout->setContentsMargins(0, 0, 0, 0);
}

void QtLayoutUtil::center(QLayout* layout) {
    layout->setAlignment(Qt::AlignCenter);
}
