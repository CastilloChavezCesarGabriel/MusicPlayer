#ifndef I_PLAYER_VIEW_H
#define I_PLAYER_VIEW_H

#include "IPlayerListener.h"
#include "IPlaylistPanel.h"
#include "ISearchPanel.h"
#include "IControlPanel.h"
#include "INotification.h"
#include "IDialog.h"
#include "IAudioPlayer.h"

class IPlayerView : public IPlaylistPanel, public ISearchPanel, public IControlPanel,
                    public INotification, public IDialog, public IAudioPlayer {
public:
    ~IPlayerView() override = default;
    virtual void add(IPlayerListener* listener) = 0;
};

#endif //I_PLAYER_VIEW_H