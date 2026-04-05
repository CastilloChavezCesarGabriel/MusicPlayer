#include "TitleDescending.h"
#include "../model/QuickSort.h"

TitleDescending::TitleDescending() : SortMode("Title \xe2\x96\xbc", new QuickSort()) {}

void TitleDescending::apply(Model& model) {
    model.sort(*criteria_);
    model.reverse();
}