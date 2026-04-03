#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "Song.h"
#include "IPlaylistVisitor.h"
#include <vector>

class SortingAlgorithm : public IPlaylistVisitor {
public:
    ~SortingAlgorithm() override = default;
    virtual void sort(std::vector<Song>& songs) = 0;
};

#endif //SORTING_ALGORITHM_H