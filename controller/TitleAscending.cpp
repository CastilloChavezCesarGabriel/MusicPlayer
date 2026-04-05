#include "TitleAscending.h"

TitleAscending::TitleAscending() : SortMode("Title \xe2\x96\xb2") {}

void TitleAscending::apply(Model& model) {
    model.sort(criteria_);
}
