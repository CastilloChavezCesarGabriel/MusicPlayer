#ifndef REPEAT_MODE_H
#define REPEAT_MODE_H

#include "IRepeatMode.h"
#include "Playlist.h"
#include "PlaybackNotifier.h"
#include <vector>
#include <memory>

class RepeatMode {
private:
    Playlist& playlist_;
    PlaybackNotifier& notifier_;
    std::vector<std::unique_ptr<IRepeatMode>> modes_;
    int index_ = 0;

public:
    RepeatMode(Playlist& playlist, PlaybackNotifier& notifier);
    void advance();
    void apply();
};

#endif //REPEAT_MODE_H
