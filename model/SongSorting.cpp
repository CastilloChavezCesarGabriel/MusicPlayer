#include "SongSorting.h"

SongSorting::SongSorting() = default;

void SongSorting::shellSort(std::vector<Song>& song) {
    const std::size_t total = song.size();
    for (std::size_t interval = total / 2; interval > 0; interval /= 2) {
        for (std::size_t i = interval; i < total; i++) {
            Song swapValue = song[i];
            const int swapNumber = Song::extractNumber(swapValue.getName());
            std::size_t j;
            for (j = i; j >= interval && Song::extractNumber(song[j - interval].getName()) > swapNumber; j -= interval) {
                song[j] = song[j - interval];
            }
            song[j] = swapValue;
        }
    }
}

void SongSorting::quickSort(std::vector<Song>& song, const std::size_t left, const std::size_t right) {
    if (left < right) {
        const std::size_t pivotIndex = partition(song, left, right);
        if (pivotIndex > 0) quickSort(song, left, pivotIndex - 1);
        quickSort(song, pivotIndex + 1, right);
    }
}

std::size_t SongSorting::partition(std::vector<Song>& song, const std::size_t left, const std::size_t right) {
    const std::string pivot = song[right].getName();
    const std::string pivotName = Song::extractName(pivot);
    std::size_t i = left - 1;

    for (std::size_t j = left; j < right; j++) {
        std::string songName = Song::extractName(song[j].getName());
        if (songName < pivotName) {
            i++;
            std::swap(song[i], song[j]);
        }
    }
    std::swap(song[i + 1], song[right]);
    return i + 1;
}
