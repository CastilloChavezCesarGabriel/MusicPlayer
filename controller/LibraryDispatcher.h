#ifndef LIBRARY_DISPATCHER_H
#define LIBRARY_DISPATCHER_H

#include "model/MusicPlayer.h"
#include "../view/ILibraryView.h"
#include "../view/ILibraryControl.h"

class LibraryDispatcher final : public ILibraryControl {
private:
    MusicPlayer& music_player_;
    ILibraryView& view_;

public:
    LibraryDispatcher(MusicPlayer& musicPlayer, ILibraryView& view);

    void add() override;
    void remove(int index) override;
    void drop(const std::vector<std::string>& paths) override;
};

#endif //LIBRARY_DISPATCHER_H
