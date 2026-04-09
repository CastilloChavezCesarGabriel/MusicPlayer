#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "model/core/Song.h"
#include "model/arrangement/ISortingAlgorithm.h"
#include "model/events/IPlaylistVisitor.h"
#include "model/events/IPlaybackListener.h"
#include "model/arrangement/Arrangement.h"
#include <vector>
#include <functional>

class Playlist {
private:
    std::vector<Song> songs_;
    Arrangement arrangement_;
    IPlaylistVisitor& deleter_;
    int current_song_ = -1;

public:
    explicit Playlist(IPlaylistVisitor& deleter);

    void add(const Song& song);
    void remove(int index);
    void sort(ISortingAlgorithm& criteria);
    void reverse();
    void restore();
    void shuffle();
    void clear();
    void select(int index, IPlaybackListener& listener);
    void pick(const std::string& name, IPlaybackListener& listener);
    void advance(IPlaybackListener& listener);
    void retreat(IPlaybackListener& listener);
    void play(IPlaylistVisitor& player) const;
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;
    bool hasNext() const;
    bool hasSelected() const;

private:
    void rearrange(const std::function<void()>& operation);
    void locate(const Song& target);
    void notify(IPlaybackListener& listener) const;
};

#endif //PLAYLIST_H