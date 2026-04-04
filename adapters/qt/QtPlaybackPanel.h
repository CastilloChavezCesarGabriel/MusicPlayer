#ifndef QT_PLAYBACK_PANEL_H
#define QT_PLAYBACK_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../view/IPlayerListener.h"

class QtPlaybackPanel final : public QWidget {
    Q_OBJECT
private:
    IPlayerListener& player_listener_;
    QPushButton* toggle_button_;
    QPushButton* repeat_button_;
    QPushButton* next_button_;
    QPushButton* previous_button_;

    void setup();
    void wire();

public:
    QtPlaybackPanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void enable(bool state) const;
    void toggle(bool playing) const;
    void repeat(int mode) const;
};

#endif //QT_PLAYBACK_PANEL_H