#include "QtToolbar.h"
#include <QVBoxLayout>

QtToolbar::QtToolbar(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
}

void QtToolbar::setup() {
    auto* sorting = new QHBoxLayout();
    auto* files = new QHBoxLayout();

    sort_by_number_button = new QPushButton("Sort by number", this);
    sort_by_name_button = new QPushButton("Sort by name", this);
    sorting->addWidget(sort_by_number_button);
    sorting->addWidget(sort_by_name_button);
    sorting->setAlignment(Qt::AlignCenter);

    add_button_ = new QPushButton("Add Song", this);
    remove_button_ = new QPushButton("Remove Song", this);
    skip_button_ = new QPushButton("Skip Ad", this);
    skip_button_->setVisible(false);
    files->addWidget(add_button_);
    files->addWidget(remove_button_);
    files->setAlignment(Qt::AlignCenter);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(sorting);
    layout->addWidget(skip_button_, 0, Qt::AlignCenter);
    layout->addLayout(files);
}

void QtToolbar::wire() {
    connect(add_button_, &QPushButton::clicked, this, &QtToolbar::addClicked);
    connect(remove_button_, &QPushButton::clicked, this, &QtToolbar::removeClicked);
    connect(skip_button_, &QPushButton::clicked, this, &QtToolbar::skipClicked);
    connect(sort_by_number_button, &QPushButton::clicked, this, &QtToolbar::sortByNumberClicked);
    connect(sort_by_name_button, &QPushButton::clicked, this, &QtToolbar::sortByNameClicked);
}

void QtToolbar::enable(const bool state) const {
    add_button_->setEnabled(state);
    remove_button_->setEnabled(state);
    sort_by_number_button->setEnabled(state);
    sort_by_name_button->setEnabled(state);
}

void QtToolbar::reveal(const bool visible) const {
    skip_button_->setVisible(visible);
}
