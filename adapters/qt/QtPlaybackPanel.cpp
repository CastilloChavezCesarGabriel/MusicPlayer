#include "QtPlaybackPanel.h"
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QStyle>
#include <filesystem>

static std::string resolve(const std::string& path) {
    return std::filesystem::current_path().string() + path;
}

QtPlaybackPanel::QtPlaybackPanel(IPlayerListener& listener, QWidget* parent)
    : QWidget(parent), player_listener_(listener) {
    setup();
    wire();
}

void QtPlaybackPanel::setup() {
    auto* layout = new QHBoxLayout(this);

    shuffle_button_ = new QPushButton(this);
    shuffle_button_->setObjectName("shuffle_button");
    shuffle_button_->setIconSize(QSize(16, 20));
    previous_button_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_button_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_button_->setObjectName("toggle_button");
    next_button_ = new QPushButton("\xe2\x8f\xad", this);
    repeat_button_ = new QPushButton(this);
    repeat_button_->setObjectName("repeat_button");
    repeat_button_->setIconSize(QSize(16, 16));

    layout->addWidget(shuffle_button_);
    layout->addWidget(previous_button_);
    layout->addWidget(toggle_button_);
    layout->addWidget(next_button_);
    layout->addWidget(repeat_button_);
    layout->setAlignment(Qt::AlignCenter);

    paint(shuffle_button_, "/resources/icons/shuffle.png");
    paint(repeat_button_, "/resources/icons/repeat.png");
    enable(false);
}

void QtPlaybackPanel::wire() {
    connect(toggle_button_, &QPushButton::clicked, this, [this]() {
        player_listener_.onToggle();
    });
    connect(repeat_button_, &QPushButton::clicked, this, [this]() {
        player_listener_.onRepeat();
    });
    connect(shuffle_button_, &QPushButton::clicked, this, [this]() {
        player_listener_.onShuffle();
    });
    connect(next_button_, &QPushButton::clicked, this, [this]() { player_listener_.onAdvance(); });
    connect(previous_button_, &QPushButton::clicked, this, [this]() { player_listener_.onRetreat(); });
}

void QtPlaybackPanel::enable(const bool state) const {
    shuffle_button_->setEnabled(state);
    toggle_button_->setEnabled(state);
    repeat_button_->setEnabled(state);
    next_button_->setEnabled(state);
    previous_button_->setEnabled(state);
}

void QtPlaybackPanel::toggle(const bool playing) const {
    toggle_button_->setText(playing ? "\xe2\x8f\xb8" : "\xe2\x96\xb6");
}

void QtPlaybackPanel::paint(QPushButton* button, const std::string& path) {
    QPixmap pixmap(QString::fromStdString(resolve(path)));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.end();
    button->setIcon(QIcon(pixmap));
    button->setText("");
}

void QtPlaybackPanel::repeat(const int mode) const {
    paint(repeat_button_, mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    repeat_button_->setIconSize(mode == 1 ? QSize(20, 20) : QSize(18, 18));
    repeat_button_->setProperty("active", mode == 2);
    repeat_button_->style()->unpolish(repeat_button_);
    repeat_button_->style()->polish(repeat_button_);
}