#include "TitleDescending.h"

TitleDescending::TitleDescending() : SortMode("Title \xe2\x96\xbc") {}

void TitleDescending::apply(Model& model) {
    model.sort(criteria_);
    model.reverse();
}
