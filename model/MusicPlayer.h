#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "model/core/Playlist.h"
#include "model/ads/Advertisement.h"
#include "model/library/MusicLibrary.h"
#include "model/events/PlaybackNotifier.h"
#include "model/repeat/RepeatMode.h"
#include "model/events/IPlaylistVisitor.h"
#include "model/ads/IAdPolicy.h"

class MusicPlayer {
private:
    MusicLibrary music_library_;
    Playlist playlist_;
    Advertisement advertisement_;
    PlaybackNotifier notifier_;
    RepeatMode repeat_mode_;

    void broadcast();
    void refresh();

public:
    MusicPlayer(const std::string& basePath, IAdPolicy& adPolicy);

    void subscribe(IPlaybackListener& listener);
    void play(int index);
    void pick(const std::string& name);
    void advance();
    void retreat();
    void end();
    void skip();
    void repeat();
    void insert(const std::string& filePath);
    void remove(int index);
    void shuffle();
    void sort(ISortingAlgorithm& criteria);
    void reverse();
    void restore();
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
};

#endif //MUSIC_PLAYER_H