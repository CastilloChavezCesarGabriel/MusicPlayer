#ifndef I_PLAYER_LISTENER_H
#define I_PLAYER_LISTENER_H

#include "IPlaybackControl.h"
#include "ILibraryControl.h"
#include "IDisplayControl.h"

class IPlayerListener : public IPlaybackControl, public ILibraryControl, public IDisplayControl {
public:
    ~IPlayerListener() override = default;
};

#endif //I_PLAYER_LISTENER_H