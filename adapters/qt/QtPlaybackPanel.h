#ifndef QT_PLAYBACK_PANEL_H
#define QT_PLAYBACK_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../view/IPlayerListener.h"
#include "IWidgetSetup.h"

class QtPlaybackPanel final : public QWidget, public IWidgetSetup {
    Q_OBJECT
private:
    IPlayerListener& player_listener_;
    QPushButton* shuffle_button_;
    QPushButton* toggle_button_;
    QPushButton* repeat_button_;
    QPushButton* next_button_;
    QPushButton* previous_button_;

    void reset(const std::string& path) const;

public:
    explicit QtPlaybackPanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void setup() override;
    void wire() override;
    void enable(bool state) const;
    void toggle(bool playing) const;
    void repeat(int mode) const;
};

#endif //QT_PLAYBACK_PANEL_H