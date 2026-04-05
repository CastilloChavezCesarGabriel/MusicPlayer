#ifndef DATE_MODE_H
#define DATE_MODE_H

#include "SortMode.h"
#include "../model/DateSort.h"

class DateMode final : public SortMode {
private:
    DateSort criteria_;

public:
    DateMode();
    void apply(Model& model) override;
};

#endif //DATE_MODE_H
