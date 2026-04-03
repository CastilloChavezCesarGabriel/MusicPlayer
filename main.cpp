#include <QApplication>
#include <filesystem>
#include "model/Model.h"
#include "adapters/qt/QtView.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    Model model(base + "/resources/music", base + "/resources/announcements");

    QtView view;
    Controller controller(model, view);

    view.show();
    return app.exec();
}
