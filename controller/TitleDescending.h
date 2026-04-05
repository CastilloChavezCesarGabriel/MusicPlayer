#ifndef TITLE_DESCENDING_H
#define TITLE_DESCENDING_H

#include "SortMode.h"
#include "../model/QuickSort.h"

class TitleDescending final : public SortMode {
private:
    QuickSort criteria_;

public:
    TitleDescending();
    void apply(Model& model) override;
};

#endif //TITLE_DESCENDING_H
