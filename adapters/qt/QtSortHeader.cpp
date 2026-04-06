#include "QtSortHeader.h"
#include <QHBoxLayout>
#include <QWidget>

QtSortHeader::QtSortHeader(QWidget* parent)
    : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    header_ = new QPushButton("Custom", this);
    header_->setObjectName("sort_header");
    header_->setFlat(true);
    header_->setCursor(Qt::PointingHandCursor);

    layout->addWidget(header_);
    layout->setContentsMargins(0, 0, 0, 0);

    connect(header_, &QPushButton::clicked, this, &QtSortHeader::clickRequested);
}

void QtSortHeader::display(const std::string& text) const {
    header_->setText(QString::fromStdString(text));
}