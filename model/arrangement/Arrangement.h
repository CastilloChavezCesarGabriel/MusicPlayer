#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "model/core/Song.h"
#include "model/arrangement/ISortingAlgorithm.h"
#include <vector>

class Arrangement {
private:
    std::vector<Song> original_;

public:
    void sort(std::vector<Song>& songs, ISortingAlgorithm& criteria);
    void reverse(std::vector<Song>& songs);
    void restore(std::vector<Song>& songs);

private:
    void preserve(const std::vector<Song>& songs);
};

#endif //ARRANGEMENT_H