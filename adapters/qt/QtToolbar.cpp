#include "QtToolbar.h"
#include <QHBoxLayout>

QtToolbar::QtToolbar(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
}

void QtToolbar::setup() {
    auto* layout = new QHBoxLayout(this);

    add_button_ = new QPushButton("Add Song", this);
    add_button_->setObjectName("add_button");
    remove_button_ = new QPushButton("Remove Song", this);
    remove_button_->setObjectName("remove_button");
    skip_button_ = new QPushButton("⏭", this);
    skip_button_->setObjectName("skip_button");
    skip_button_->setVisible(false);

    layout->addWidget(add_button_);
    layout->addWidget(remove_button_);
    layout->addWidget(skip_button_);
    layout->setAlignment(Qt::AlignCenter);
}

void QtToolbar::wire() {
    connect(add_button_, &QPushButton::clicked, this, &QtToolbar::addClicked);
    connect(remove_button_, &QPushButton::clicked, this, &QtToolbar::removeClicked);
    connect(skip_button_, &QPushButton::clicked, this, &QtToolbar::skipClicked);
}

void QtToolbar::enable(const bool state) const {
    add_button_->setEnabled(state);
    remove_button_->setEnabled(state);
}

void QtToolbar::reveal(const bool visible) const {
    skip_button_->setVisible(visible);
}