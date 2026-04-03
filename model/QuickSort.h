#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include "SortingAlgorithm.h"

class QuickSort final : public SortingAlgorithm {
private:
    std::string title_;

    void visit(const std::string& name, const std::string& path) override;
    int divide(std::vector<Song>& songs, int startBound, int endBound);

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //QUICK_SORT_H