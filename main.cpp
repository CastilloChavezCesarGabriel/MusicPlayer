#include <filesystem>
#include "model/Model.h"
#include "adapters/qt/QtView.h"
#include "adapters/qt/QtStyler.h"
#include "controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const std::string base = std::filesystem::current_path().string();
    QtStyler::apply(app, base + "/resources/styles.qss");

    Model model(base + "/resources");
    QtView view;
    Controller controller(model, view);

    view.show();
    return app.exec();
}