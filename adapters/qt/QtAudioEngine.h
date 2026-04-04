#ifndef QT_AUDIO_ENGINE_H
#define QT_AUDIO_ENGINE_H

#include "QtProgressPanel.h"
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <string>

class QtAudioEngine final : public QWidget {
    Q_OBJECT
private:
    QMediaPlayer* media_player_;
    QAudioOutput* audio_output_;
    QTimer* ad_timer_;
    QtProgressPanel* progress_bar_;

    void setup();

public:
    explicit QtAudioEngine(QWidget* parent = nullptr);
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