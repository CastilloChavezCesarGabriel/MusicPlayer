#ifndef QT_PLAYBACK_PANEL_H
#define QT_PLAYBACK_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../view/IPlaybackControl.h"
#include "IWidgetSetup.h"

class QtPlaybackPanel final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    IPlaybackControl& playback_listener_;
    QPushButton* shuffle_button_;
    QPushButton* toggle_button_;
    QPushButton* repeat_button_;
    QPushButton* next_button_;
    QPushButton* previous_button_;

    static void paint(QPushButton* button, const std::string& path);

public:
    explicit QtPlaybackPanel(IPlaybackControl& listener, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
    void toggle(bool playing) const;
    void repeat(int mode) const;
};

#endif //QT_PLAYBACK_PANEL_H