#ifndef TITLE_ASCENDING_H
#define TITLE_ASCENDING_H

#include "SortMode.h"
#include "../model/QuickSort.h"

class TitleAscending final : public SortMode {
private:
    QuickSort criteria_;

public:
    TitleAscending();
    void apply(Model& model) override;
};

#endif //TITLE_ASCENDING_H
