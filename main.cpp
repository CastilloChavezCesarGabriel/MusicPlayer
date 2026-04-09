#include <filesystem>
#include "model/MusicPlayer.h"
#include "model/Dice.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Dice dice;
    MusicPlayer musicPlayer(base + "/resources", dice);
    QtView view;
    Controller controller(musicPlayer, view);

    view.show();
    return app.exec();
}