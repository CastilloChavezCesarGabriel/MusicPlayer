#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include "SortingAlgorithm.h"

class QuickSort final : public SortingAlgorithm {
private:
    std::string title_;
    std::vector<Song>* songs_ = nullptr;

    void visit(const std::string& name, const std::string& path) override;
    int divide(int startBound, int endBound);

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //QUICK_SORT_H