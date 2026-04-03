#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include "MusicLibrary.h"
#include "SortingAlgorithm.h"
#include "IPlaylistVisitor.h"
#include "IPlaybackListener.h"
#include <vector>

class Playlist {
private:
    std::vector<Song> songs_;
    MusicLibrary& library_;
    int current_song_ = -1;

public:
    explicit Playlist(MusicLibrary& library);

    void add(const Song& song);
    void remove(int index);
    void sort(SortingAlgorithm& criteria);
    void shuffle();
    void clear();
    void select(int index, IPlaybackListener& listener);
    void advance(IPlaybackListener& listener);
    void retreat(IPlaybackListener& listener);
    void play(IPlaylistVisitor& player) const;
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
    bool hasNext() const;
    bool hasSelected() const;

private:
    void notify(IPlaybackListener& listener) const;
};

#endif //PLAYLIST_H