#ifndef DURATION_MODE_H
#define DURATION_MODE_H

#include "SortMode.h"
#include "../model/DurationSort.h"

class DurationMode final : public SortMode {
private:
    DurationSort criteria_;

public:
    DurationMode();
    void apply(Model& model) override;
};

#endif //DURATION_MODE_H
