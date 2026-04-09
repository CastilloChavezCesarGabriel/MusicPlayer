#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "model/arrangement/ISortingAlgorithm.h"
#include "model/events/IPlaylistVisitor.h"
#include <utility>

class QuickSort final : public ISortingAlgorithm, public IPlaylistVisitor {
private:
    std::string title_;

    void visit(const std::string& name, const std::string& path) override;
    int divide(std::vector<Song>& songs, const std::pair<int, int>& bounds);

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //QUICK_SORT_H