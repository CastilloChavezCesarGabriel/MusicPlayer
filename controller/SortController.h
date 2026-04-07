#ifndef SORT_CONTROLLER_H
#define SORT_CONTROLLER_H

#include "SortMode.h"
#include "../model/Model.h"
#include "../view/IPlayerView.h"
#include <vector>
#include <memory>

class SortController {
private:
    Model& model_;
    IPlayerView& view_;
    std::vector<std::unique_ptr<SortMode>> modes_;
    int index_ = -1;

public:
    SortController(Model& model, IPlayerView& view);
    void cycle();
};

#endif //SORT_CONTROLLER_H