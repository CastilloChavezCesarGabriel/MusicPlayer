#include "QtDisplayWidget.h"
#include <QObject>

QtDisplayWidget::QtDisplayWidget(QWidget* parent, QVBoxLayout* layout) {
    search_input_ = new QLineEdit(parent);
    search_input_->setPlaceholderText("Search...");
    sort_header_ = new QtSortHeader(parent);
    display_ = new QtPlaylistDisplay(parent);
    search_overlay_ = new QtSearchOverlay(parent);

    layout->addWidget(search_input_);
    layout->addWidget(sort_header_);
    layout->addWidget(display_);
}

void QtDisplayWidget::wire(IDisplayControl& listener) {
    listener_ = &listener;

    QObject::connect(sort_header_, &QtSortHeader::clickRequested, sort_header_, [this]() {
        listener_->sort();
    });
    QObject::connect(search_input_, &QLineEdit::textChanged, search_input_, [this](const QString& text) {
        listener_->search(text.toStdString());
    });
    QObject::connect(search_overlay_, &QtSearchOverlay::selectRequested, search_overlay_, [this](const std::string& name) {
        listener_->pick(name);
        search_input_->clear();
    });
}

void QtDisplayWidget::refresh(const std::vector<std::string>& names) { display_->refresh(names); }
void QtDisplayWidget::highlight(const int index) { display_->highlight(index); }
void QtDisplayWidget::suggest(const std::vector<std::string>& names) { search_overlay_->display(names); }
void QtDisplayWidget::dismiss() { search_overlay_->clear(); }
void QtDisplayWidget::sort(const std::string& label) { sort_header_->display(label); }
void QtDisplayWidget::remove() const { display_->remove(); }

void QtDisplayWidget::onSelect(const std::function<void(int)>& callback) const {
    QObject::connect(display_, &QtPlaylistDisplay::selectRequested, display_, callback);
}

void QtDisplayWidget::onRemoveRequest(const std::function<void(int)>& callback) const {
    QObject::connect(display_, &QtPlaylistDisplay::removeRequested, display_, callback);
}

void QtDisplayWidget::onDrop(const std::function<void(const std::vector<std::string>&)>& callback) const {
    QObject::connect(display_, &QtPlaylistDisplay::dropRequested, display_, callback);
}
