#ifndef QT_VIEW_H
#define QT_VIEW_H

#include "../../view/IPlayerView.h"
#include "QtPlaybackPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QAudioOutput>

class QtView final : public QWidget, public IPlayerView {
    Q_OBJECT
private:
    IPlayerListener* listener_ = nullptr;
    QtPlaybackPanel* playback_ = nullptr;
    QtVolumePanel* volume_ = nullptr;
    QtToolbar* toolbar_ = nullptr;
    QListView* playlist_;
    QStringListModel* list_model_;
    QLineEdit* search_;
    QMediaPlayer* media_;
    QAudioOutput* output_;

    void setup();
    void wire();
    void bind();

public:
    explicit QtView(QWidget* parent = nullptr);

    void add(IPlayerListener* listener) override;
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void enable(bool state) override;
    void reveal(bool visible) override;
    void notify(const std::string& message, bool success) override;
    bool confirm(const std::string& message) override;
    std::string browse() override;
    void play(const std::string& path) override;
    void resume() override;
    void pause() override;
    void stop() override;
    void adjust(double volume) override;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif //QT_VIEW_H