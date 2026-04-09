#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H

#include "model/core/Song.h"
#include <vector>

class ISortingAlgorithm {
public:
    virtual ~ISortingAlgorithm() = default;
    virtual void sort(std::vector<Song>& songs) = 0;
};

#endif //SORTING_ALGORITHM_H