#ifndef QT_VIEW_FACTORY_H
#define QT_VIEW_FACTORY_H

#include "../../view/IPlaybackControl.h"
#include "../../view/IDisplayControl.h"
#include "QtPlaybackPanel.h"
#include "QtVolumePanel.h"
#include "QtToolbar.h"
#include "QtNotification.h"
#include "QtDialog.h"
#include <QWidget>

class QtViewFactory {
public:
    static QtPlaybackPanel* createPlayback(IPlaybackControl& listener, QWidget* parent);
    static QtVolumePanel* createVolume(IDisplayControl& listener, QWidget* parent);
    static QtToolbar* createToolbar(QWidget* parent);
    static QtNotification* createNotification(QWidget* parent);
    static QtDialog* createDialog(QWidget* parent);
};

#endif //QT_VIEW_FACTORY_H