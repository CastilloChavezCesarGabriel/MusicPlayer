#include "QtPlaybackPanel.h"

QtPlaybackPanel::QtPlaybackPanel(IPlayerListener& listener, QWidget* parent)
    : QWidget(parent), listener_(listener) {
    setup();
    wire();
}

void QtPlaybackPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    previous_button_ = new QPushButton("Previous", this);
    play_button_ = new QPushButton("Play", this);
    pause_button_ = new QPushButton("Pause", this);
    repeat_button_ = new QPushButton("Repeat", this);
    repeat_button_->setCheckable(true);
    next_button_ = new QPushButton("Next", this);

    layout->addWidget(previous_button_);
    layout->addWidget(play_button_);
    layout->addWidget(pause_button_);
    layout->addWidget(repeat_button_);
    layout->addWidget(next_button_);
    layout->setAlignment(Qt::AlignCenter);
}

void QtPlaybackPanel::wire() {
    connect(play_button_, &QPushButton::clicked, this, [this]() { listener_.onResume(); });
    connect(pause_button_, &QPushButton::clicked, this, [this]() { listener_.onPause(); });
    connect(repeat_button_, &QPushButton::clicked, this, [this]() { listener_.onRepeat(); });
    connect(next_button_, &QPushButton::clicked, this, [this]() { listener_.onAdvance(); });
    connect(previous_button_, &QPushButton::clicked, this, [this]() { listener_.onRetreat(); });
}

void QtPlaybackPanel::enable(const bool state) const {
    play_button_->setEnabled(state);
    pause_button_->setEnabled(state);
    repeat_button_->setEnabled(state);
    next_button_->setEnabled(state);
    previous_button_->setEnabled(state);
}