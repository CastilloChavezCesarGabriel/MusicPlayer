#include "QtAudioEngine.h"
#include "QtLayoutUtil.h"
#include <QVBoxLayout>
#include <QAudioDevice>
#include <QUrl>

QtAudioEngine::QtAudioEngine(QWidget* parent) : QWidget(parent) {
    setup();
    wire();
    monitor();
}

void QtAudioEngine::setup() {
    media_player_ = new QMediaPlayer(this);
    audio_output_ = new QAudioOutput(this);
    audio_output_->setVolume(0.5);
    media_player_->setAudioOutput(audio_output_);

    ad_timer_ = new QTimer(this);
    ad_timer_->setSingleShot(true);
    progress_bar_ = new QtProgressPanel(*media_player_, this);

    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);
    layout->addWidget(progress_bar_);
}

void QtAudioEngine::wire() {
    connect(media_player_, &QMediaPlayer::mediaStatusChanged, this, [this]
        (const QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            emit endRequested();
        }
    });

    connect(ad_timer_, &QTimer::timeout, this, [this]() {
        emit revealRequested();
    });
}

void QtAudioEngine::monitor() {
    auto* devices = new QMediaDevices(this);
    connect(devices, &QMediaDevices::audioOutputsChanged, this, [this]() {
        audio_output_->setDevice(QMediaDevices::defaultAudioOutput());
    });
}

void QtAudioEngine::start() {
    media_player_->play();
    emit toggleRequested(true);
}

void QtAudioEngine::play(const std::string& path) {
    media_player_->stop();
    media_player_->setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
    start();
}

void QtAudioEngine::resume() {
    start();
}

void QtAudioEngine::pause() {
    media_player_->pause();
    emit toggleRequested(false);
}

void QtAudioEngine::stop() const {
    media_player_->stop();
}

void QtAudioEngine::adjust(const double volume) const {
    audio_output_->setVolume(volume);
}

void QtAudioEngine::schedule(const int milliseconds) const {
    ad_timer_->stop();
    ad_timer_->start(milliseconds);
}

void QtAudioEngine::cancel() const {
    ad_timer_->stop();
}

void QtAudioEngine::enable(const bool state) const {
    progress_bar_->enable(state);
}