#ifndef REPEAT_STRATEGY_H
#define REPEAT_STRATEGY_H

#include "Playlist.h"
#include "IPlaybackListener.h"

class RepeatStrategy {
protected:
    int code_;

public:
    explicit RepeatStrategy(int code);
    virtual ~RepeatStrategy() = default;
    virtual bool apply(Playlist& playlist, IPlaybackListener& listener) = 0;
    void announce(IPlaybackListener& listener) const;
};

#endif //REPEAT_STRATEGY_H