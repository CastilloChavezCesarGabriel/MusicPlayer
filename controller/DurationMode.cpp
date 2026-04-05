#include "DurationMode.h"

DurationMode::DurationMode() : SortMode("Duration \xe2\x96\xb2") {}

void DurationMode::apply(Model& model) {
    model.sort(criteria_);
}
