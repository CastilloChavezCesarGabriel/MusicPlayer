#include "DateMode.h"

DateMode::DateMode() : SortMode("Date Added \xe2\x96\xb2") {}

void DateMode::apply(Model& model) {
    model.sort(criteria_);
}
