#include "Model.h"
#include "ShellSort.h"
#include "QuickSort.h"
#include <filesystem>

Model::Model(const std::string& musicPath, const std::string& adsPath)
    : music_library_(musicPath), playlist_(music_library_), advertisement_(adsPath) {

    for (const Song& song : music_library_.load()) {
        playlist_.add(song);
    }
    playlist_.shuffle();
    advertisement_.load();
}

void Model::add(IPlaybackListener& listener) {
    listener_ = &listener;
    channel_ = new Channel(listener);
}

void Model::play(const int index) {
    playlist_.select(index, *listener_);

    if (Advertisement::schedule()) {
        listener_->onEnabled(false);
        advertisement_.interrupt(*listener_);
    } else {
        broadcast();
    }
}

void Model::advance() {
    if (playlist_.hasNext()) {
        playlist_.advance(*listener_);
        broadcast();
    }
}

void Model::retreat() {
    playlist_.retreat(*listener_);
    broadcast();
}

void Model::end() {
    if (advertisement_.conclude()) {
        resume();
        return;
    }

    if (repeat_song_) {
        broadcast();
        return;
    }

    advance();
}

void Model::skip() {
    if (advertisement_.conclude()) {
        resume();
    }
}

void Model::broadcast() const {
    playlist_.play(*channel_);
}

void Model::refresh() const {
    listener_->onChanged();
}

void Model::resume() const {
    listener_->onReveal(false);
    listener_->onEnabled(true);
    broadcast();
}

void Model::repeat() {
    repeat_song_ = !repeat_song_;
    listener_->onFeedback(repeat_song_ ? "Repeat enabled" : "Repeat disabled", true);
}

void Model::insert(const std::string& filePath) {
    if (!validate(filePath)) return;

    playlist_.add(music_library_.import(filePath));
    refresh();
    listener_->onFeedback("Song added successfully!", true);
}

bool Model::validate(const std::string& filePath) const {
    if (filePath.empty() || !MusicLibrary::isSupported(filePath)) {
        listener_->onFeedback("Unsupported file type.", false);
        return false;
    }

    const std::filesystem::path source(filePath);
    if (music_library_.contains(source.filename().string())) {
        listener_->onFeedback("This song already exists.", false);
        return false;
    }

    return true;
}

void Model::remove(const int index) {
    playlist_.remove(index);
    refresh();
}

void Model::sort(const bool byName) {
    if (byName) {
        QuickSort byTitle;
        playlist_.sort(byTitle);
    } else {
        ShellSort byNumber;
        playlist_.sort(byNumber);
    }
    refresh();
}

void Model::accept(IPlaylistVisitor& visitor) const {
    playlist_.accept(visitor);
}

void Model::search(const std::string& query, IPlaylistVisitor& visitor) const {
    playlist_.search(query, visitor);
}