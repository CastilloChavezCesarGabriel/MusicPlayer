#ifndef I_PLAYBACK_BOARD_H
#define I_PLAYBACK_BOARD_H

#include "IPlaybackControl.h"

class IPlaybackBoard {
public:
    virtual ~IPlaybackBoard() = default;
    virtual void attach(IPlaybackControl& listener) = 0;
};

#endif //I_PLAYBACK_BOARD_H