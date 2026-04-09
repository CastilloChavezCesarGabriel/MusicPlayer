#ifndef QT_LIBRARY_WIDGET_H
#define QT_LIBRARY_WIDGET_H

#include "../../view/ILibraryView.h"
#include "../../view/ILibraryControl.h"
#include "QtToolbar.h"
#include "QtDialog.h"
#include <QWidget>
#include <QVBoxLayout>
#include <functional>

class QtLibraryWidget final : public ILibraryView {
private:
    QtToolbar* toolbar_;
    QtDialog* dialog_;
    ILibraryControl* listener_ = nullptr;

public:
    QtLibraryWidget(QWidget* parent, QVBoxLayout* layout);
    void bind(ILibraryControl& listener);
    std::string browse() override;
    bool confirm(const std::string& message) override;
    void reveal(bool visible) override;
    void enable(bool state) override;
    void onSkip(const std::function<void()>& callback) const;
    void onRemove(const std::function<void()>& callback) const;
};

#endif //QT_LIBRARY_WIDGET_H
