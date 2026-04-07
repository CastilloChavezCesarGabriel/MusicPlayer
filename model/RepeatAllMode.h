#ifndef REPEAT_ALL_MODE_H
#define REPEAT_ALL_MODE_H

#include "RepeatStrategy.h"

class RepeatAllMode final : public RepeatStrategy {
public:
    RepeatAllMode();
    void apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //REPEAT_ALL_MODE_H