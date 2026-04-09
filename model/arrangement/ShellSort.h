#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include "model/arrangement/ISortingAlgorithm.h"
#include "model/events/IPlaylistVisitor.h"

class ShellSort : public ISortingAlgorithm, public IPlaylistVisitor {
protected:
    long long key_ = 0;

public:
    void sort(std::vector<Song>& songs) override;
};

#endif //SHELL_SORT_H
