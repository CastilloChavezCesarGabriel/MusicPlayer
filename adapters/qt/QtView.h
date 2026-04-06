#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "../../view/IPlayerView.h"
#include "QtPlaybackPanel.h"
#include "QtToolbar.h"
#include "QtAudioEngine.h"
#include "QtPlaylistDisplay.h"
#include <QWidget>
#include <QLineEdit>

class QtView final : public QWidget, public IPlayerView {
    Q_OBJECT
private:
    IPlayerListener* listener_ = nullptr;
    QtPlaybackPanel* playback_ = nullptr;
    QtToolbar* toolbar_ = nullptr;
    QtAudioEngine* audio_;
    QtPlaylistDisplay* display_;

    void setup();
    void wire(const QLineEdit* search);
    void bind();

public:
    explicit QtView(QWidget* parent = nullptr);

    void add(IPlayerListener* listener) override;
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void suggest(const std::vector<std::string>& names) override;
    void dismiss() override;
    void enable(bool state) override;
    void reveal(bool visible) override;
    void schedule(int delay) override;
    void cancel() override;
    void repeat(int mode) override;
    void sort(const std::string& label) override;
    void notify(const std::string& message, bool success) override;
    bool confirm(const std::string& message) override;
    std::string browse() override;
    void play(const std::string& path) override;
    void resume() override;
    void pause() override;
    void stop() override;
    void adjust(int volume) override;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif //QT_VIEW_H