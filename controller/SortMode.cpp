#include "SortMode.h"

SortMode::SortMode(const std::string& label, SortingAlgorithm* criteria)
    : label_(label), criteria_(criteria) {}

void SortMode::apply(Model& model) {
    model.sort(*criteria_);
}

void SortMode::display(IPlayerView& view) const {
    view.sort(label_);
}