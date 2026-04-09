#ifndef REPEAT_MODE_H
#define REPEAT_MODE_H

#include "RepeatStrategy.h"
#include "Playlist.h"
#include "PlaybackNotifier.h"
#include <vector>
#include <memory>

class RepeatMode {
private:
    Playlist& playlist_;
    PlaybackNotifier& notifier_;
    std::vector<std::unique_ptr<RepeatStrategy>> modes_;
    int index_ = 0;

public:
    RepeatMode(Playlist& playlist, PlaybackNotifier& notifier);
    void advance();
    bool apply() const;
};

#endif //REPEAT_MODE_H