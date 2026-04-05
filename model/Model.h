#ifndef MODEL_H
#define MODEL_H

#include "Playlist.h"
#include "Advertisement.h"
#include "MusicLibrary.h"
#include "PlaybackNotifier.h"
#include "IPlaylistVisitor.h"

class Model {
private:
    MusicLibrary music_library_;
    Playlist playlist_;
    Advertisement advertisement_;
    PlaybackNotifier notifier_;
    int repeat_mode_ = 0;

public:
    explicit Model(const std::string& basePath);

    void subscribe(IPlaybackListener& listener);
    void play(int index);
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

private:
    void broadcast();
    void refresh();
};

#endif //MODEL_H