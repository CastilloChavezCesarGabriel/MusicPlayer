#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "model/repeat/RepeatStrategy.h"

class NoRepeatMode final : public RepeatStrategy {
public:
    NoRepeatMode();
    bool apply(Playlist& playlist, IPlaybackListener& listener) override;
};

#endif //NO_REPEAT_MODE_H