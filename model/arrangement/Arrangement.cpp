#include "model/arrangement/Arrangement.h"
#include <algorithm>

void Arrangement::sort(std::vector<Song>& songs, ISortingAlgorithm& criteria) {
    preserve(songs);
    criteria.sort(songs);
}

void Arrangement::reverse(std::vector<Song>& songs) {
    preserve(songs);
    std::ranges::reverse(songs);
}

void Arrangement::restore(std::vector<Song>& songs) {
    if (original_.empty()) return;
    songs = original_;
    original_.clear();
}

void Arrangement::preserve(const std::vector<Song>& songs) {
    if (original_.empty()) {
        original_ = songs;
    }
}