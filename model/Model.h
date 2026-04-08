#ifndef MODEL_H
#define MODEL_H

#include "MusicPlayer.h"

class Model {
private:
    MusicPlayer music_player_;

public:
    explicit Model(const std::string& basePath);

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

#endif //MODEL_H