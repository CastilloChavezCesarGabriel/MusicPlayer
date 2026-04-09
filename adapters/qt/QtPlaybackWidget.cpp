#include "QtPlaybackWidget.h"
#include "QtViewFactory.h"
#include <QObject>

QtPlaybackWidget::QtPlaybackWidget(QWidget* parent, QVBoxLayout* layout) {
    audio_ = new QtAudioEngine(parent);
    notification_ = QtViewFactory::createNotification(parent);
    layout->addWidget(audio_);

    QObject::connect(audio_, &QtAudioEngine::endRequested, audio_, [this]() {
        if (listener_) listener_->end();
    });
    QObject::connect(audio_, &QtAudioEngine::toggleRequested, audio_, [this](const bool playing) {
        if (panel_) panel_->toggle(playing);
    });
}

void QtPlaybackWidget::attach(IPlaybackControl& listener) {
    listener_ = &listener;
    panel_ = new QtPlaybackPanel(listener, audio_->parentWidget());
    volume_ = new QtVolumePanel(listener, audio_->parentWidget());
    audio_->parentWidget()->layout()->addWidget(panel_);
    audio_->parentWidget()->layout()->addWidget(volume_);
}

void QtPlaybackWidget::play(const std::string& path) { audio_->play(path); }
void QtPlaybackWidget::pause() { audio_->pause(); }
void QtPlaybackWidget::resume() { audio_->resume(); }
void QtPlaybackWidget::stop() { audio_->stop(); }
void QtPlaybackWidget::adjust(const int volume) { audio_->adjust(volume / 100.0); }

void QtPlaybackWidget::enable(const bool state) {
    if (panel_) panel_->enable(state);
    audio_->enable(state);
}

void QtPlaybackWidget::schedule(const int delay) { audio_->schedule(delay); }
void QtPlaybackWidget::cancel() { audio_->cancel(); }

void QtPlaybackWidget::repeat(const int mode) {
    if (panel_) panel_->repeat(mode);
}

void QtPlaybackWidget::notify(const std::string& message, const bool success) {
    notification_->notify(message, success);
}

void QtPlaybackWidget::onReveal(const std::function<void()>& callback) const {
    QObject::connect(audio_, &QtAudioEngine::revealRequested, audio_, callback);
}