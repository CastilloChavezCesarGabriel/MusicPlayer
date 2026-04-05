#include "QtPlaybackPanel.h"

QtPlaybackPanel::QtPlaybackPanel(IPlayerListener& listener, QWidget* parent)
    : QWidget(parent), player_listener_(listener) {
    setup();
    wire();
}

void QtPlaybackPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    previous_button_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_button_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_button_->setObjectName("toggle_button");
    next_button_ = new QPushButton("\xe2\x8f\xad", this);
    repeat_button_ = new QPushButton("\xf0\x9f\x94\x81", this);
    repeat_button_->setObjectName("repeat_button");

    layout->addWidget(previous_button_);
    layout->addWidget(toggle_button_);
    layout->addWidget(next_button_);
    layout->addWidget(repeat_button_);
    layout->setAlignment(Qt::AlignCenter);
}

void QtPlaybackPanel::wire() {
    connect(toggle_button_, &QPushButton::clicked, this, [this]() {
        player_listener_.onToggle();
    });
    connect(repeat_button_, &QPushButton::clicked, this, [this]() {
        player_listener_.onRepeat();
    });
    connect(next_button_, &QPushButton::clicked, this, [this]() { player_listener_.onAdvance(); });
    connect(previous_button_, &QPushButton::clicked, this, [this]() { player_listener_.onRetreat(); });
}

void QtPlaybackPanel::enable(const bool state) const {
    toggle_button_->setEnabled(state);
    repeat_button_->setEnabled(state);
    next_button_->setEnabled(state);
    previous_button_->setEnabled(state);
}

void QtPlaybackPanel::toggle(const bool playing) const {
    toggle_button_->setText(playing ? "\xe2\x8f\xb8" : "\xe2\x96\xb6");
}

void QtPlaybackPanel::reset(const std::string& icon) const {
    repeat_button_->setText(QString::fromStdString(icon));
    repeat_button_->setStyleSheet("");
}

void QtPlaybackPanel::repeat(const int mode) const {
    if (mode == 2) {
        repeat_button_->setText("\xf0\x9f\x94\x81");
        repeat_button_->setStyleSheet(
            "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #a78bfa, stop:1 #7c3aed);"
            "color: white;"
        );
    } else {
        reset(mode == 1 ? "\xf0\x9f\x94\x82" : "\xf0\x9f\x94\x81");
    }
}