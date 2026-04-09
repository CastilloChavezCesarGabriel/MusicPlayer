#ifndef LIBRARY_DISPATCHER_H
#define LIBRARY_DISPATCHER_H

#include "../model/MusicPlayer.h"
#include "../view/IPlayerView.h"
#include "../view/ILibraryControl.h"

class LibraryDispatcher final : public ILibraryControl {
private:
    MusicPlayer& music_player_;
    IPlayerView& view_;

public:
    LibraryDispatcher(MusicPlayer& musicPlayer, IPlayerView& view);

    void onAdd() override;
    void onRemove(int index) override;
    void onDrop(const std::vector<std::string>& paths) override;
};

#endif //LIBRARY_DISPATCHER_H