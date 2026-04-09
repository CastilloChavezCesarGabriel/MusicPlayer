#include "SortController.h"
#include "TitleDescending.h"
#include "CustomMode.h"
#include "model/arrangement/QuickSort.h"
#include "model/arrangement/DurationSort.h"
#include "model/arrangement/DateSort.h"

SortController::SortController(MusicPlayer& musicPlayer, IDisplayView& view)
    : music_player_(musicPlayer), view_(view) {
    modes_.push_back(std::make_unique<SortMode>("Title \xe2\x96\xb2", new QuickSort()));
    modes_.push_back(std::make_unique<TitleDescending>());
    modes_.push_back(std::make_unique<SortMode>("Duration \xe2\x96\xb2", new DurationSort()));
    modes_.push_back(std::make_unique<SortMode>("Date \xe2\x96\xb2", new DateSort()));
    modes_.push_back(std::make_unique<CustomMode>());
}

void SortController::cycle() {
    index_ = (index_ + 1) % static_cast<int>(modes_.size());
    modes_[index_]->apply(music_player_);
    modes_[index_]->display(view_);
}
