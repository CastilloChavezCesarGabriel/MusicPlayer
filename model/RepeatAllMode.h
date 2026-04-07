#ifndef REPEAT_ALL_MODE_H
#define REPEAT_ALL_MODE_H

#include "IRepeatMode.h"

class RepeatAllMode final : public IRepeatMode {
public:
    void apply(Playlist& playlist, IPlaybackListener& listener) override;
    void announce(IPlaybackListener& listener) const override;
};

#endif //REPEAT_ALL_MODE_H
