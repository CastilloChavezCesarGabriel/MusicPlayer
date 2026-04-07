#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "RepeatStrategy.h"

class NoRepeatMode final : public RepeatStrategy {
public:
    NoRepeatMode();
    void apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //NO_REPEAT_MODE_H
