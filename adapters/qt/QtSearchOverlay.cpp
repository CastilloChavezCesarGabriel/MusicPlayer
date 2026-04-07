#include "QtSearchOverlay.h"
#include "QtLayoutUtil.h"
#include <QVBoxLayout>

QtSearchOverlay::QtSearchOverlay(QWidget* parent) : QWidget(parent) {
    setup();
    setVisible(false);
}

void QtSearchOverlay::setup() {
    results_ = new QListWidget(this);
    results_->setObjectName("search_results");

    auto* layout = new QVBoxLayout(this);
    QtLayoutUtil::flatten(layout);
    layout->addWidget(results_);

    connect(results_, &QListWidget::itemDoubleClicked, this, [this](const QListWidgetItem* item) {
        emit selectRequested(item->text().toStdString());
    });
}

void QtSearchOverlay::align() {
    if (!parentWidget()) return;
    const int margin = 8;
    const int top = 75;
    const int width = parentWidget()->width() - margin * 2;
    const int height = std::min(200, results_->count() * 36 + 8);
    setGeometry(margin, top, width, height);
}

void QtSearchOverlay::display(const std::vector<std::string>& names) {
    results_->clear();
    for (const auto& name : names) {
        results_->addItem(QString::fromStdString(name));
    }
    align();
    setVisible(!names.empty());
    raise();
}

void QtSearchOverlay::clear() {
    results_->clear();
    setVisible(false);
}
