#ifndef SORT_MODE_H
#define SORT_MODE_H

#include "../model/Model.h"
#include "../view/IPlayerView.h"
#include <string>

class SortMode {
private:
    std::string label_;

public:
    explicit SortMode(const std::string& label);
    virtual ~SortMode() = default;
    virtual void apply(Model& model) = 0;
    void display(IPlayerView& view) const;
};

#endif //SORT_MODE_H
