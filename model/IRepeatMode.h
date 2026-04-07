#ifndef I_REPEAT_MODE_H
#define I_REPEAT_MODE_H

#include "Playlist.h"
#include "IPlaybackListener.h"

class IRepeatMode {
public:
    virtual ~IRepeatMode() = default;
    virtual void apply(Playlist& playlist, IPlaybackListener& listener) = 0;
    virtual void announce(IPlaybackListener& listener) const = 0;
};

#endif //I_REPEAT_MODE_H
