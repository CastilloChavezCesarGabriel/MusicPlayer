#ifndef QT_PLAYBACK_WIDGET_H
#define QT_PLAYBACK_WIDGET_H

#include "../../view/IPlaybackView.h"
#include "../../view/IPlaybackControl.h"
#include "QtPlaybackPanel.h"
#include "QtAudioEngine.h"
#include "QtNotification.h"
#include "QtVolumePanel.h"
#include <QWidget>
#include <QVBoxLayout>
#include <functional>

class QtPlaybackWidget final : public IPlaybackView {
private:
    QtPlaybackPanel* panel_ = nullptr;
    QtAudioEngine* audio_;
    QtNotification* notification_;
    QtVolumePanel* volume_ = nullptr;
    IPlaybackControl* listener_ = nullptr;

public:
    QtPlaybackWidget(QWidget* parent, QVBoxLayout* layout);
    void attach(IPlaybackControl& listener);
    void play(const std::string& path) override;
    void pause() override;
    void resume() override;
    void stop() override;
    void adjust(int volume) override;
    void enable(bool state) override;
    void schedule(int delay) override;
    void cancel() override;
    void repeat(int mode) override;
    void notify(const std::string& message, bool success) override;
    void onReveal(const std::function<void()>& callback) const;
};

#endif //QT_PLAYBACK_WIDGET_H