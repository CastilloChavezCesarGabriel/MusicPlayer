#ifndef REPEAT_ONE_MODE_H
#define REPEAT_ONE_MODE_H

#include "IRepeatMode.h"

class RepeatOneMode final : public IRepeatMode {
public:
    void apply(Playlist& playlist, IPlaybackListener& listener) override;
    void announce(IPlaybackListener& listener) const override;
};

#endif //REPEAT_ONE_MODE_H
