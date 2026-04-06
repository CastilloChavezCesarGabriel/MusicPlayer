#ifndef QT_AUDIO_ENGINE_H
#define QT_AUDIO_ENGINE_H

#include "QtProgressPanel.h"
#include "IWidgetSetup.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QTimer>
#include <string>

class QtAudioEngine final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    QMediaPlayer* media_player_;
    QAudioOutput* audio_output_;
    QTimer* ad_timer_;
    QtProgressPanel* progress_bar_;

    void monitor();
    void start();

public:
    explicit QtAudioEngine(QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void play(const std::string& path);
    void resume();
    void pause();
    void stop() const;
    void adjust(double volume) const;
    void schedule(int milliseconds) const;
    void cancel() const;
    void enable(bool state) const;

signals:
    void endRequested();
    void revealRequested();
    void toggleRequested(bool playing);
};

#endif //QT_AUDIO_ENGINE_H