#include <filesystem>
#include <QApplication>
#include "model/MusicPlayer.h"
#include "model/ads/Dice.h"
#include "model/ads/RandomAdPolicy.h"
#include "adapters/qt/QtStyler.h"
#include "adapters/qt/QtPlaybackWidget.h"
#include "adapters/qt/QtLibraryWidget.h"
#include "adapters/qt/QtDisplayWidget.h"
#include "controller/PlaybackDispatcher.h"
#include "controller/LibraryDispatcher.h"
#include "controller/DisplayDispatcher.h"
#include "controller/PlaybackBridge.h"
#include "controller/DisplayBridge.h"
#include "controller/LibraryBridge.h"
#include "model/events/PlaybackEventNotifier.h"
#include "model/events/DisplayEventNotifier.h"
#include "model/events/LibraryEventNotifier.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    RandomAdPolicy ad_policy(dice);
    MusicPlayer musicPlayer(base + "/resources", ad_policy);

    QWidget shell;
    shell.setObjectName("MainWindow");
    shell.setWindowTitle("Music Player");
    auto* layout = new QVBoxLayout(&shell);

    QtDisplayWidget display(&shell, layout);
    QtPlaybackWidget playback(&shell, layout);
    QtLibraryWidget library(&shell, layout);

    PlaybackDispatcher playback_dispatcher(musicPlayer, playback);
    LibraryDispatcher  library_dispatcher(musicPlayer, library);
    DisplayDispatcher  display_dispatcher(musicPlayer, display);

    playback.attach(playback_dispatcher);
    library.bind(library_dispatcher);
    display.wire(display_dispatcher);

    playback.onReveal([&library]() { library.reveal(true); });
    library.onRemove([&display]() { display.remove(); });
    library.onSkip([&playback_dispatcher]() { playback_dispatcher.skip(); });
    display.onSelect([&playback_dispatcher](const int index) { playback_dispatcher.play(index); });
    display.onRemoveRequest([&library_dispatcher](const int index) { library_dispatcher.remove(index); });
    display.onDrop([&library_dispatcher](const std::vector<std::string>& paths) { library_dispatcher.drop(paths); });

    PlaybackEventNotifier playback_events;
    DisplayEventNotifier  display_events;
    LibraryEventNotifier  library_events;

    musicPlayer.subscribe(playback_events);
    musicPlayer.subscribe(display_events);
    musicPlayer.subscribe(library_events);

    PlaybackBridge playback_bridge(playback);
    DisplayBridge  display_bridge(musicPlayer, display);
    LibraryBridge  library_bridge(library);

    playback_events.subscribe(playback_bridge);
    display_events.subscribe(display_bridge);
    library_events.subscribe(library_bridge);

    shell.show();
    return app.exec();
}