#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include "SortingAlgorithm.h"

class ShellSort : public SortingAlgorithm {
protected:
    long long key_ = 0;

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H