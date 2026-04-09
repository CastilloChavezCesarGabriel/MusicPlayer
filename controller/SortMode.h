#ifndef SORT_MODE_H
#define SORT_MODE_H

#include <string>
#include <memory>
#include "model/MusicPlayer.h"
#include "../view/IDisplayView.h"
#include "model/arrangement/ISortingAlgorithm.h"

class SortMode {
private:
    std::string label_;

protected:
    std::unique_ptr<ISortingAlgorithm> criteria_;

public:
    SortMode(const std::string& label, ISortingAlgorithm* criteria);
    virtual ~SortMode() = default;
    virtual void apply(MusicPlayer& musicPlayer);
    void display(IDisplayView& view) const;
};

#endif //SORT_MODE_H