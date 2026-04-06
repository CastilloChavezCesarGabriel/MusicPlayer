#include "QtView.h"
#include "QtViewFactory.h"
#include "QtSearchOverlay.h"
#include <QVBoxLayout>
#include "QtVolumePanel.h"
#include "QtSortHeader.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>

QtView::QtView(QWidget* parent) : QWidget(parent) {
    setObjectName("MainWindow");
    audio_ = new QtAudioEngine(this);

    connect(audio_, &QtAudioEngine::endRequested, this, [this]() {
        if (listener_) listener_->onEnd();
    });

    connect(audio_, &QtAudioEngine::revealRequested, this, [this]() {
        if (toolbar_) toolbar_->reveal(true);
    });

    connect(audio_, &QtAudioEngine::toggleRequested, this, [this](const bool playing) {
        if (playback_) playback_->toggle(playing);
    });

    setup();
    setAcceptDrops(true);
}

void QtView::setup() {
    setWindowTitle("Music Player");

    auto* main = new QVBoxLayout(this);
    auto* search = new QLineEdit(this);
    search->setPlaceholderText("Search...");
    sort_header_ = new QtSortHeader(this);
    display_ = new QtPlaylistDisplay(this);
    search_overlay_ = new QtSearchOverlay(this);

    main->addWidget(search);
    main->addWidget(sort_header_);
    main->addWidget(display_);
    main->addWidget(audio_);

    connect(sort_header_, &QtSortHeader::clickRequested, this, [this]() {
        if (listener_) listener_->onSort();
    });

    wire(search);
}

void QtView::wire(const QLineEdit* search) {
    connect(display_, &QtPlaylistDisplay::selectRequested, this, [this](const int index) {
        if (listener_) listener_->onPlay(index);
    });

    connect(search, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (listener_) listener_->onSearch(text.toStdString());
    });
}

void QtView::add(IPlayerListener* listener) {
    listener_ = listener;

    auto* main = layout();
    playback_ = QtViewFactory::createPlayback(*listener, this);
    auto* volume = QtViewFactory::createVolume(*listener, this);
    toolbar_ = QtViewFactory::createToolbar(this);

    main->addWidget(playback_);
    main->addWidget(volume);
    main->addWidget(toolbar_);

    bind();
}

void QtView::bind() {
    connect(toolbar_, &QtToolbar::addClicked, this, [this]() {
        listener_->onAdd();
    });
    connect(toolbar_, &QtToolbar::removeClicked, display_, &QtPlaylistDisplay::remove);
    connect(display_, &QtPlaylistDisplay::removeRequested, this, [this](const int index) {
        listener_->onRemove(index);
    });
    connect(toolbar_, &QtToolbar::skipClicked, this, [this]() {
        listener_->onSkip();
    });
    connect(toolbar_, &QtToolbar::shuffleClicked, this, [this]() {
        listener_->onShuffle();
    });
}

void QtView::refresh(const std::vector<std::string>& names) {
    display_->refresh(names);
}

void QtView::highlight(const int index) {
    display_->highlight(index);
}

void QtView::suggest(const std::vector<std::string>& names) {
    search_overlay_->display(names);
}

void QtView::dismiss() {
    search_overlay_->clear();
}

void QtView::enable(const bool state) {
    if (playback_) playback_->enable(state);
    if (toolbar_) toolbar_->enable(state);
    audio_->enable(state);
}

void QtView::schedule(const int delay) {
    audio_->schedule(delay);
}

void QtView::cancel() {
    audio_->cancel();
}

void QtView::repeat(const int mode) {
    if (playback_) playback_->repeat(mode);
}

void QtView::sort(const std::string& label) {
    sort_header_->display(label);
}

void QtView::reveal(const bool visible) {
    if (toolbar_) toolbar_->reveal(visible);
}

void QtView::notify(const std::string& message, const bool success) {
    QMessageBox::information(this, success ? "Success" : "Oops",
                             QString::fromStdString(message));
}

bool QtView::confirm(const std::string& message) {
    return QMessageBox::question(this, "",
        QString::fromStdString(message),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

std::string QtView::browse() {
    return QFileDialog::getOpenFileName(this).toStdString();
}

void QtView::play(const std::string& path) {
    audio_->play(path);
}

void QtView::resume() {
    audio_->resume();
}

void QtView::pause() {
    audio_->pause();
}

void QtView::stop() {
    audio_->stop();
}

void QtView::adjust(const int volume) {
    audio_->adjust(volume / 100.0);
}

void QtView::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void QtView::dropEvent(QDropEvent* event) {
    if (!listener_) return;
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    std::vector<std::string> paths;
    for (const auto& url : urls) {
        paths.push_back(url.toLocalFile().toStdString());
    }
    listener_->onDrop(paths);
}