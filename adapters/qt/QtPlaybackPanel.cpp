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

    previous_button_ = new QPushButton("\xe2\x8f\xae", this);
    toggle_button_ = new QPushButton("\xe2\x96\xb6", this);
    toggle_button_->setObjectName("toggle_button");
    next_button_ = new QPushButton("\xe2\x8f\xad", this);
    repeat_button_ = new QPushButton(this);
    repeat_button_->setObjectName("repeat_button");
    repeat_button_->setIconSize(QSize(16, 16));

    layout->addWidget(previous_button_);
    layout->addWidget(toggle_button_);
    layout->addWidget(next_button_);
    layout->addWidget(repeat_button_);
    layout->setAlignment(Qt::AlignCenter);

    reset("/resources/icons/repeat.png");
    enable(false);
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

void QtPlaybackPanel::reset(const std::string& path) const {
    QPixmap pixmap(QString::fromStdString(resolve(path)));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), Qt::white);
    painter.end();
    repeat_button_->setIcon(QIcon(pixmap));
    repeat_button_->setText("");
}

void QtPlaybackPanel::repeat(const int mode) const {
    reset(mode == 1 ? "/resources/icons/repeat_one.png" : "/resources/icons/repeat.png");
    repeat_button_->setProperty("active", mode == 2);
    repeat_button_->style()->unpolish(repeat_button_);
    repeat_button_->style()->polish(repeat_button_);
}