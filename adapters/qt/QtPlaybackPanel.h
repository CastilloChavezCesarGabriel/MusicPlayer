#ifndef QT_PLAYBACK_PANEL_H
#define QT_PLAYBACK_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../view/IPlayerListener.h"

class QtPlaybackPanel final : public QWidget {
    Q_OBJECT
private:
    IPlayerListener& listener_;
    QPushButton* play_button_;
    QPushButton* pause_button_;
    QPushButton* repeat_button_;
    QPushButton* next_button_;
    QPushButton* previous_button_;

    void setup();
    void wire();

public:
    QtPlaybackPanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void enable(bool state) const;
};

#endif //QT_PLAYBACK_PANEL_H