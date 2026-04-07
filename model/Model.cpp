#include "Model.h"

Model::Model(const std::string& basePath) : music_player_(basePath) {}

void Model::subscribe(IPlaybackListener& listener) {
    music_player_.subscribe(listener);
}

void Model::play(const int index) {
    music_player_.play(index);
}

void Model::pick(const std::string& name) {
    music_player_.pick(name);
}

void Model::advance() {
    music_player_.advance();
}

void Model::retreat() {
    music_player_.retreat();
}

void Model::end() {
    music_player_.end();
}

void Model::skip() {
    music_player_.skip();
}

void Model::repeat() {
    music_player_.repeat();
}

void Model::insert(const std::string& filePath) {
    music_player_.insert(filePath);
}

void Model::remove(const int index) {
    music_player_.remove(index);
}

void Model::shuffle() {
    music_player_.shuffle();
}

void Model::sort(SortingAlgorithm& criteria) {
    music_player_.sort(criteria);
}

void Model::reverse() {
    music_player_.reverse();
}

void Model::restore() {
    music_player_.restore();
}

void Model::accept(IPlaylistVisitor& visitor) const {
    music_player_.accept(visitor);
}

void Model::search(const std::string& query, IPlaylistVisitor& visitor) const {
    music_player_.search(query, visitor);
}