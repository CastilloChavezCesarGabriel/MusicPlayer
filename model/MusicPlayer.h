#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "Playlist.h"
#include "Advertisement.h"
#include "MusicLibrary.h"
#include "PlaybackNotifier.h"
#include "RepeatMode.h"
#include "IPlaylistVisitor.h"

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
    explicit MusicPlayer(const std::string& basePath);

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
    void sort(SortingAlgorithm& criteria);
    void reverse();
    void restore();
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
};

#endif //MUSIC_PLAYER_H