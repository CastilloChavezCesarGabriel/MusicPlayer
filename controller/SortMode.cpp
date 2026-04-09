#include "SortMode.h"

SortMode::SortMode(const std::string& label, ISortingAlgorithm* criteria)
    : label_(label), criteria_(criteria) {}

void SortMode::apply(MusicPlayer& musicPlayer) {
    musicPlayer.sort(*criteria_);
}

void SortMode::display(IDisplayView& view) const {
    view.sort(label_);
}