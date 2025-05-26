#include "Controller.h"
#include <QLineEdit>
#include <QTimer>
#include <QRandomGenerator>

Controller::Controller(Model *model, View *view, QObject *parent)
        : QObject(parent), model_(model), view_(view) {

    media_player_ = new QMediaPlayer(this);
    audio_output_ = new QAudioOutput(this);
    media_player_->setAudioOutput(audio_output_);

    connect(view, &View::onPlayRequested, this, &Controller::onPlaySelected);
    connect(view, &View::onPauseRequested, media_player_, &QMediaPlayer::pause);
    connect(view, &View::onRepeatRequested,this, &Controller::onRepeat);
    connect(view, &View::onNextRequested, this, &Controller::onPlayNext);
    connect(view, &View::onPreviousRequested, this, &Controller::onPlayPrevious);
    connect(view, &View::onAddRequested, this, &Controller::onAdd);
    connect(view, &View::onRemoveRequested, this, &Controller::onRemove);
    connect(view, &View::onSkipAdRequested, this, &Controller::onSkipAd);
    connect(view, &View::onSortByNumberRequested, this, &Controller::onSortByNumber);
    connect(view, &View::onSortByNameRequested, this, &Controller::onSortByName);

    connect(view, &View::onVolumeChanged, this, &Controller::onUpdateVolume);
    connect(view, &View::onSearchChanged, this, &Controller::onSearch);

    connect(model, &Model::songsUpdated, view, &View::updatePlaylist);
    connect(view, &View::filesDropped, this, &Controller::handleDrop);
    connect(media_player_, &QMediaPlayer::mediaStatusChanged, this, &Controller::handleMediaStatus);
    connect(model, &Model::disableButtons, view, [view]() { view->enableButtons(false); });
    connect(model, &Model::userFeedback, view, &View::showUserFeedback);

    view->updatePlaylist(model->getSongs());
}

void Controller::onPlaySelected() {
    selected_id_ = onSaveId();
    const int song_id = model_->getId(selected_id_);

    if (media_player_->playbackState() == QMediaPlayer::PausedState) {
        media_player_->play();
        return;
    }

    processSelection(song_id, false);
}

void Controller::onPlayNext() {
    const int nextId = model_->getId(current_id_) + 1;
    if (nextId <= model_->getSongs().size() - 1) {
        processSelection(nextId, false);
    } else {
        media_player_->stop();
    }
}

void Controller::onPlayPrevious() {
    const int previousId = model_->getId(current_id_) - 1;
    if (previousId >= 0) {
        processSelection(previousId, false);
    }
}

void Controller::onRepeat() {
    repeat_ = !repeat_;
}

void Controller::onSkipAd() {
    if (!model_->isPlayingAd()) return;
    media_player_->stop();
    handleAdStatus();
}

void Controller::onUpdateVolume(const int volume) const {
    const qreal volumeFactor = volume / 100.0;
    audio_output_->setVolume(volumeFactor);
    view_->updateVolume(volume);
}

void Controller::onAdd() {
    const QString filePath = QFileDialog::getOpenFileName(view_);
    if (!filePath.isEmpty()) return;

    model_->add(filePath.toStdString());
    view_->updatePlaylist(model_->getSongs());

    const auto& songs = model_->getSongs();
    if (!songs.empty()) {
        const std::string newId = model_->getIndex(songs.size() - 1);
        onRestoreId(newId);
    }
}

void Controller::onRemove() {
    selected_id_ = onSaveId();
    if (selected_id_.empty()) return;

    const std::string filePath = model_->getFilePath(model_->getId(selected_id_));
    if (filePath.empty()) return;

    if (view_->showConfirmation("Are you sure you wanna delete this song?")) {
        model_->remove(filePath);
        updatePlaylist(selected_id_);

        if (selected_id_ == current_id_) {
            media_player_->stop();
            current_id_.clear();
        }
    }
}

void Controller::onSortByNumber() {
    const std::string current_id = onSaveId();
    model_->sortByNumber();
    updatePlaylist(current_id);
}

void Controller::onSortByName() {
    const std::string current_id = onSaveId();
    model_->sortByName();
    updatePlaylist(current_id);
}

void Controller::onSearch(const QString& text) const {
    const std::string query = text.toStdString();
    const std::vector<Song> results = model_->search(query);
    std::vector<std::string> songNames;
    for (const Song& song : results) {
        songNames.push_back(song.getName());
    }
    view_->updatePlaylist(songNames);
}

void Controller::updatePlaylist(const std::string &id) {
    view_->updatePlaylist(model_->getSongs());
    onRestoreId(id);
    view_->enableButtons(true);
}

void Controller::handleDrop(const QList<QUrl> &urls) {
    if (urls.isEmpty()) return;

    current_id_ = onSaveId();
    const std::vector<std::string> paths = toStringVector(urls);

    model_->drop(paths);
    view_->updatePlaylist(model_->getSongs());

    if (!current_id_.empty() && model_->getId(current_id_) != -1) {
        onRestoreId(current_id_);
        return;
    }

    const std::string originalId = model_->getIndex(0);
    if (!originalId.empty()) {
        onRestoreId(originalId);
        return;
    }

    view_->clearSelection();
}

bool Controller::isPlayback() {
    return QRandomGenerator::global()->bounded(100) < 25;
}

void Controller::onPlay(const std::string &filePath) const {
    if (filePath.empty()) return;
    media_player_->stop();
    media_player_->setSource(QUrl::fromLocalFile(filePath.c_str()));
    media_player_->play();
}

void Controller::handlePlayback(const int song_id) const {
    view_->showSkipAd(false);
    const std::string filePath = model_->getFilePath(song_id);
    onPlay(filePath);
}

void Controller::processSelection(const int song_id, const bool updateSelectedId) {
    if (updateSelectedId) {
        selected_id_ = model_->getIndex(song_id);
    }

    current_id_ = model_->getIndex(song_id);
    onRestoreId(current_id_);

    if (isPlayback()) {
        song_stack_.push(song_id);
        processRandomAd();
    } else {
        handlePlayback(song_id);
    }
}

void Controller::processRandomAd() const {
    const std::string path = model_->getRandomAd();
    if (path.empty()) return;

    model_->setPlayingAd(true);
    view_->enableButtons(false);
    const int delay = QRandomGenerator::global()->bounded(5, 10) * 1000;
    QTimer::singleShot(delay, this, [this]() { view_->showSkipAd(true); });
    onPlay(path);
}

void Controller::handleMediaStatus(const QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        if (model_->isPlayingAd()) {
            handleAdStatus();
        } else {
            handleSongStatus();
        }
    }
}

void Controller::handleAdStatus() {
    model_->setPlayingAd(false);
    view_->showSkipAd(false);
    view_->enableButtons(true);

    if (!song_stack_.empty()) {
        const int nextIndex = song_stack_.top();
        song_stack_.pop();
        view_->updateSelection(nextIndex);
        onPlaySelected();
    } else {
        onPlayNext();
    }
}

void Controller::handleSongStatus() {
    if (repeat_) {
        const int currentSongId = model_->getId(current_id_);
        if (currentSongId != -1) {
            handlePlayback(currentSongId);
        }
        return;
    }

    const int nextId = model_->getId(current_id_) + 1;
    if (nextId >= model_->getSongs().size()) {
        if (!isPlayback()) {
            media_player_->stop();
        }
        return;
    }

    if (isPlayback()) {
        processSelection(nextId, true);
    } else {
        onRestoreId(model_->getIndex(nextId));
        onPlaySelected();
    }
}

std::string Controller::onSaveId() const {
    const QModelIndex currentId = view_->playlistView()->currentIndex();
    if (!currentId.isValid()) return {};
    return model_->getIndex(currentId.row());
}

void Controller::onRestoreId(const std::string &song_id) {
    int restoredIndex = model_->getId(song_id);

    if (restoredIndex == -1 && model_->isPlayingAd()) {
        restoredIndex = model_->getId(current_id_);
    }

    if (restoredIndex != -1) {
        view_->updateSelection(restoredIndex);
        current_id_ = model_->getIndex(restoredIndex);
    }
}

std::vector<std::string> Controller::toStringVector(const QList<QUrl>& input) {
    std::vector<std::string> result;
    result.reserve(input.size());
    for (const auto& url : input) {
        result.push_back(url.toLocalFile().toStdString());
    }
    return result;
}
