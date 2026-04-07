#include "QtLayoutHelper.h"

void QtLayoutHelper::flatten(QLayout* layout) {
    layout->setContentsMargins(0, 0, 0, 0);
}

void QtLayoutHelper::center(QLayout* layout) {
    layout->setAlignment(Qt::AlignCenter);
}
