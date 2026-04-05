#ifndef DURATION_SORT_H
#define DURATION_SORT_H
#include "ShellSort.h"

class DurationSort final : public ShellSort {
private:
    void visit(const std::string& name, const std::string& path) override;
};

#endif //DURATION_SORT_H