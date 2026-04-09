#ifndef DATE_SORT_H
#define DATE_SORT_H
#include "model/arrangement/ShellSort.h"

class DateSort final : public ShellSort {
private:
    void visit(const std::string& name, const std::string& path) override;
};

#endif //DATE_SORT_H