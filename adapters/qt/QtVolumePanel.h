#ifndef QT_VOLUME_PANEL_H
#define QT_VOLUME_PANEL_H

#include "../../view/IPlayerListener.h"
#include <QWidget>
#include <QSlider>
#include <QLabel>

class QtVolumePanel final : public QWidget {
    Q_OBJECT
private:
    IPlayerListener& listener_;
    QSlider* slider_;
    QLabel* label_;

public:
    QtVolumePanel(IPlayerListener& listener, QWidget* parent = nullptr);
    void adjust(int volume) const;
};

#endif //QT_VOLUME_PANEL_H