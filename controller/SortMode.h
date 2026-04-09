#ifndef SORT_MODE_H
#define SORT_MODE_H

#include <string>
#include <memory>
#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../model/SortingAlgorithm.h"

class SortMode {
private:
    std::string label_;

protected:
    std::unique_ptr<SortingAlgorithm> criteria_;

public:
    SortMode(const std::string& label, SortingAlgorithm* criteria);
    virtual ~SortMode() = default;
    virtual void apply(MusicPlayer& musicPlayer);
    void display(IPlayerView& view) const;
};

#endif //SORT_MODE_H