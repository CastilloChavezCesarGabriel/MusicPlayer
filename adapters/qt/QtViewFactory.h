#ifndef QT_VIEW_FACTORY_H
#define QT_VIEW_FACTORY_H

#include "../../view/IPlayerListener.h"
#include "QtPlaybackPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include <QWidget>

class QtViewFactory {
public:
    static QtPlaybackPanel* createPlayback(IPlayerListener& listener, QWidget* parent);
    static QtVolumePanel* createVolume(IPlayerListener& listener, QWidget* parent);
    static QtToolbar* createToolbar(QWidget* parent);
};

#endif //QT_VIEW_FACTORY_H