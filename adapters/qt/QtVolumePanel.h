#ifndef QT_VOLUME_PANEL_H
#define QT_VOLUME_PANEL_H

#include "../../view/IDisplayControl.h"
#include <QSlider>
#include <QLabel>

class QtVolumePanel final : public QWidget {
    Q_OBJECT
private:
    IDisplayControl& display_listener_;
    QSlider* slider_;
    QLabel* label_;

public:
    explicit QtVolumePanel(IDisplayControl& listener, QWidget* parent = nullptr);
    void adjust(int volume) const;
};

#endif //QT_VOLUME_PANEL_H
