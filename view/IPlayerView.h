#ifndef I_PLAYER_VIEW_H
#define I_PLAYER_VIEW_H

#include "IPlaylistPanel.h"
#include "ISearchPanel.h"
#include "IControlPanel.h"
#include "INotification.h"
#include "IDialog.h"
#include "IAudioPlayer.h"
#include "IPlaybackBoard.h"
#include "ILibraryBoard.h"
#include "IDisplayBoard.h"

class IPlayerView : public IPlaylistPanel, public ISearchPanel, public IControlPanel,
                    public INotification, public IDialog, public IAudioPlayer,
                    public IPlaybackBoard, public ILibraryBoard, public IDisplayBoard {
public:
    ~IPlayerView() override = default;
};

#endif //I_PLAYER_VIEW_H