#include "QtView.h"
#include "QtViewFactory.h"
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

QtView::QtView(QWidget* parent) : QWidget(parent) {
    media_ = new QMediaPlayer(this);
    output_ = new QAudioOutput(this);
    media_->setAudioOutput(output_);

    connect(media_, &QMediaPlayer::mediaStatusChanged, this, [this](const QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia && listener_) {
            listener_->onEnd();
        }
    });

    setup();
    setAcceptDrops(true);
}

void QtView::setup() {
    setWindowTitle("Music Player");

    auto* main = new QVBoxLayout(this);

    search_ = new QLineEdit(this);
    search_->setPlaceholderText("Search...");

    playlist_ = new QListView(this);
    list_model_ = new QStringListModel(this);
    playlist_->setModel(list_model_);

    main->addWidget(search_);
    main->addWidget(playlist_);

    wire();
}

void QtView::wire() {
    connect(playlist_, &QListView::doubleClicked, this, [this](const QModelIndex& index) {
        if (listener_) listener_->onPlay(index.row());
    });
    connect(search_, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (listener_) listener_->onSearch(text.toStdString());
    });
}

void QtView::add(IPlayerListener* listener) {
    listener_ = listener;

    auto* main = layout();
    playback_ = QtViewFactory::createPlayback(*listener, this);
    volume_ = QtViewFactory::createVolume(*listener, this);
    toolbar_ = QtViewFactory::createToolbar(this);

    main->addWidget(playback_);
    main->addWidget(volume_);
    main->addWidget(toolbar_);

    bind();
}

void QtView::bind() {
    connect(toolbar_, &QtToolbar::addClicked, this, [this]() {
        listener_->onAdd();
    });
    connect(toolbar_, &QtToolbar::removeClicked, this, [this]() {
        const QModelIndex index = playlist_->currentIndex();
        if (index.isValid()) listener_->onRemove(index.row());
    });
    connect(toolbar_, &QtToolbar::skipClicked, this, [this]() {
        listener_->onSkip();
    });
    connect(toolbar_, &QtToolbar::sortByNumberClicked, this, [this]() {
        listener_->onSort(false);
    });
    connect(toolbar_, &QtToolbar::sortByNameClicked, this, [this]() {
        listener_->onSort(true);
    });
}

void QtView::refresh(const std::vector<std::string>& names) {
    QStringList list;
    for (const auto& name : names) {
        list.append(QString::fromStdString(name));
    }
    list_model_->setStringList(list);
}

void QtView::highlight(const int index) {
    if (index >= 0 && index < list_model_->rowCount()) {
        playlist_->setCurrentIndex(list_model_->index(index, 0));
    }
}

void QtView::enable(const bool state) {
    if (playback_) playback_->enable(state);
    if (toolbar_) toolbar_->enable(state);
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
    media_->stop();
    media_->setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
    media_->play();
}

void QtView::resume() {
    media_->play();
}

void QtView::pause() {
    media_->pause();
}

void QtView::stop() {
    media_->stop();
}

void QtView::adjust(const double volume) {
    output_->setVolume(volume);
    if (volume_) volume_->adjust(static_cast<int>(volume * 100));
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