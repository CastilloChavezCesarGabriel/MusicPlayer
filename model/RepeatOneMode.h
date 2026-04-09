#ifndef REPEAT_ONE_MODE_H
#define REPEAT_ONE_MODE_H

#include "RepeatStrategy.h"

class RepeatOneMode final : public RepeatStrategy {
public:
    RepeatOneMode();
    bool apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //REPEAT_ONE_MODE_H