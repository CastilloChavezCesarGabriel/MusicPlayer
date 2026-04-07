#include "QtViewFactory.h"

QtPlaybackPanel* QtViewFactory::createPlayback(IPlayerListener& listener, QWidget* parent) {
    return new QtPlaybackPanel(listener, parent);
}

QtVolumePanel* QtViewFactory::createVolume(IPlayerListener& listener, QWidget* parent) {
    return new QtVolumePanel(listener, parent);
}

QtToolbar* QtViewFactory::createToolbar(QWidget* parent) {
    return new QtToolbar(parent);
}

QtNotification* QtViewFactory::createNotification(QWidget* parent) {
    return new QtNotification(parent);
}

QtDialog* QtViewFactory::createDialog(QWidget* parent) {
    return new QtDialog(parent);
}