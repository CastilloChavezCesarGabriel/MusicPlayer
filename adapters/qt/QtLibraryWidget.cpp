#include "QtLibraryWidget.h"
#include "QtViewFactory.h"
#include <QObject>

QtLibraryWidget::QtLibraryWidget(QWidget* parent, QVBoxLayout* layout) {
    toolbar_ = QtViewFactory::createToolbar(parent);
    dialog_ = QtViewFactory::createDialog(parent);
    layout->addWidget(toolbar_);
}

void QtLibraryWidget::bind(ILibraryControl& listener) {
    listener_ = &listener;
    QObject::connect(toolbar_, &QtToolbar::addClicked, toolbar_, [this]() {
        listener_->add();
    });
}

std::string QtLibraryWidget::browse() { return dialog_->browse(); }
bool QtLibraryWidget::confirm(const std::string& message) { return dialog_->confirm(message); }
void QtLibraryWidget::reveal(const bool visible) { toolbar_->reveal(visible); }
void QtLibraryWidget::enable(const bool state) { toolbar_->enable(state); }

void QtLibraryWidget::onSkip(const std::function<void()>& callback) const {
    QObject::connect(toolbar_, &QtToolbar::skipClicked, toolbar_, callback);
}

void QtLibraryWidget::onRemove(const std::function<void()>& callback) const {
    QObject::connect(toolbar_, &QtToolbar::removeClicked, toolbar_, callback);
}
