#include "SortMode.h"

SortMode::SortMode(const std::string& label) : label_(label) {}

void SortMode::display(IPlayerView& view) const {
    view.sort(label_);
}
