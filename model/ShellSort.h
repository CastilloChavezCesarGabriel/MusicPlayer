#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include "SortingAlgorithm.h"

class ShellSort final : public SortingAlgorithm {
private:
    int order_ = 0;

    void visit(const std::string& name, const std::string& path) override;

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H