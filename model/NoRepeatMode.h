#ifndef NO_REPEAT_MODE_H
#define NO_REPEAT_MODE_H

#include "IRepeatMode.h"

class NoRepeatMode final : public IRepeatMode {
public:
    void apply(Playlist& playlist, IPlaybackListener& listener) override;
    void announce(IPlaybackListener& listener) const override;
};

#endif //NO_REPEAT_MODE_H
