#ifndef SONG_SORTING_H
#define SONG_SORTING_H
#include "ISorting.h"
#include "Song.h"

class SongSorting final : public ISorting<Song, std::size_t, std::size_t>  {
public:
    SongSorting();
    void shellSort(std::vector<Song>& song) override;
    void quickSort(std::vector<Song>& song, std::size_t left, std::size_t right) override;

private:
    std::size_t partition(std::vector<Song>& song, std::size_t left, std::size_t right) override;
};

#endif //SONG_SORTING_H
