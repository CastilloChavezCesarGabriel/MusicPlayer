#include <filesystem>
#include "model/MusicPlayer.h"
#include "model/Dice.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "controller/PlaybackDispatcher.h"
#include "controller/LibraryDispatcher.h"
#include "controller/DisplayDispatcher.h"
#include "controller/PlaybackBridge.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    MusicPlayer musicPlayer(base + "/resources", dice);
    QtView view;

    PlaybackDispatcher playback(musicPlayer, view);
    LibraryDispatcher library(musicPlayer, view);
    DisplayDispatcher display(musicPlayer, view);
    view.attach(playback);
    view.bind(library);
    view.wire(display);

    PlaybackBridge bridge(musicPlayer, view);

    view.show();
    return app.exec();
}
