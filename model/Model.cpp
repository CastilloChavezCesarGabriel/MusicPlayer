#include "Model.h"
#include <filesystem>
#include <random>

Model::Model(QObject *parent) : QObject(parent) {
    base_path_ = std::filesystem::current_path().string();
    resources_path_ = base_path_ + "/resources";
    music_path_ = resources_path_ + "/music";
    ads_path_ = resources_path_ + "/announcements";
    loadMusic();
    loadAds();
}

std::vector<std::string> Model::getSongs() const {
    std::vector<std::string> names;
    for (const Song& song : songs_) {
        names.push_back(song.getName());
    }
    return names;
}

int Model::getId(const std::string &id) const {
    for (int i = 0; i < songs_.size(); ++i) {
        if (songs_[i].getId() == id) return i;
    }
    return -1;
}

std::string Model::getIndex(const int index) const {
    if (index >= 0 && index < songs_.size()) {
        return songs_.at(index).getId();
    }
    return {};
}

bool Model::isPlayingAd() const {
    return playing_ad_;
}

void Model::setPlayingAd(const bool state) {
    playing_ad_ = state;
}

void Model::add(const std::string &file_path) {
    if (file_path.empty() || !isExtension(file_path)) {
        emit userFeedback("❌ Unsupported file type.", false);
        return;
    }

    const std::filesystem::path path(file_path);
    const std::string filename = path.filename().string();
    std::string new_file_path = music_path_ + "/" + filename;

    if (find(new_file_path) != songs_.end()) {
        emit userFeedback("⚠️ This song already exists.", false);
        return;
    }

    save(file_path);

    const int number = songs_.size() + 1;
    songs_.emplace_back(number, filename, new_file_path);
    song_names_.push_back(filename);

    emit songsUpdated(song_names_);
    emit userFeedback("✅ Song added successfully!", true);
}

void Model::remove(const std::string &file_path) {
    if (file_path.empty()) {
        emit userFeedback("⚠️ Invalid file path.", false);
        return;
    }

    if (const auto song = find(file_path); song != songs_.end()) {
        songs_.erase(song);
        std::filesystem::remove(file_path);
        updatePlaylist();
    }else {
        emit userFeedback("❌ Song not found.", false);
    }
}

std::string Model::getFilePath(const int index) const {
    if (index < 0 || index >= songs_.size()) return {};
    return songs_[index].getFilePath();
}

void Model::drop(const std::vector<std::string> &urls) {
    for (int i = 0; i < urls.size(); ++i) {
        const std::string &file_path = urls[i];
        if (isExtension(file_path)) {
            add(file_path);
        } else {
            emit userFeedback("❌ Unsupported file type.", false);
            return;
        }
    }
}

void Model::sortByNumber() {
    sorting.shellSort(songs_);
    updatePlaylist();
}

void Model::sortByName() {
    sorting.quickSort(songs_, 0, songs_.size() - 1);
    updatePlaylist();
}

void Model::shuffle() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::ranges::shuffle(songs_, generator);
}

std::string Model::getRandomAd() const {
    if (ads_.empty()) return {};
    std::mt19937 randomEngine(std::random_device{}());
    std::uniform_int_distribution<> distribution(0, ads_.size() - 1);
    return ads_.at(distribution(randomEngine));
}

void Model::loadMusic() {
    const std::string path = music_path_;
    if (!std::filesystem::exists(path)) return;

    song_names_ = filter(path);
    songs_.clear();

    for (int i = 0; i < song_names_.size(); ++i) {
        std::string full_path = path + "/" + song_names_[i];
        const int number = i + 1;
        songs_.emplace_back(number, song_names_[i], full_path);
    }

    updatePlaylist();
    shuffle();
}

void Model::loadAds() {
    const std::string path = ads_path_;
    if (!std::filesystem::exists(path)) return;

    ads_ = filter(path);
    for (int i = 0; i < ads_.size(); ++i) {
        ads_[i] = path + "/" + ads_[i];
    }
    emit adsUpdated(ads_);
}

std::vector<std::string> Model::filter(const std::string &directory) {
    const std::filesystem::path direction(directory);
    const std::vector<std::string> filters = { ".mp3", ".wav" };
    std::vector<std::string> result;

    if (!std::filesystem::exists(direction) || !std::filesystem::is_directory(direction)) {
        return result;
    }

    for (const auto &entry : std::filesystem::directory_iterator(direction)) {
        if (entry.is_regular_file()) {
            const std::string ext = entry.path().extension().string();
            if (std::ranges::find(filters, ext) != filters.end()) {
                result.push_back(entry.path().filename().string());
            }
        }
    }

    return result;
}

bool Model::isExtension(const std::string &file_name) {
    const std::filesystem::path path(file_name);
    const std::string extension = path.extension().string();
    return extension == ".mp3" || extension == ".wav";
}

std::vector<Song>::iterator Model::find(const std::string &file_path) {
    return std::ranges::find_if(songs_, [&](const Song &song) {
        return song.getFilePath() == file_path;
    });
}

void Model::save(const std::string &file_path) const {
    const std::filesystem::path source_path(file_path);
    const std::string destination = music_path_;
    const std::filesystem::path destination_path = std::filesystem::path(destination) / source_path.filename();

    if (!std::filesystem::exists(destination_path)) {
        std::filesystem::copy_file(source_path, destination_path);
    }
}

std::vector<Song> Model::search(const std::string& query) const {
    std::vector<Song> result;
    for (const Song& song : songs_) {
        if (Song::match(song, query)) {
            result.push_back(song);
        }
    }
    return result;
}

void Model::updatePlaylist() {
    song_names_.clear();
    for (const Song &song : songs_) {
        song_names_.push_back(song.getName());
    }
    emit songsUpdated(song_names_);
}
