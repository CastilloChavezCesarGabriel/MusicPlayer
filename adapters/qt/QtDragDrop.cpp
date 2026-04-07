#include "QtDragDrop.h"
#include <QMimeData>
#include <QUrl>

void QtDragDrop::accept(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

std::vector<std::string> QtDragDrop::extract(const QDropEvent* event) {
    std::vector<std::string> paths;
    const QList<QUrl> urls = event->mimeData()->urls();
    for (const auto& url : urls) {
        paths.push_back(url.toLocalFile().toStdString());
    }
    return paths;
}