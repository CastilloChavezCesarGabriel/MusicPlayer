#ifndef TITLE_DESCENDING_H
#define TITLE_DESCENDING_H

#include "SortMode.h"

class TitleDescending final : public SortMode {
public:
    TitleDescending();
    void apply(Model& model) override;
};

#endif //TITLE_DESCENDING_H