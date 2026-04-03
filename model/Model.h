#ifndef MODEL_H
#define MODEL_H

#include "Playlist.h"
#include "Advertisement.h"
#include "MusicLibrary.h"
#include "Channel.h"
#include "IPlaybackListener.h"
#include "IPlaylistVisitor.h"

class Model {
private:
    MusicLibrary music_library_;
    Playlist playlist_;
    Advertisement advertisement_;
    IPlaybackListener* listener_ = nullptr;
    Channel* channel_ = nullptr;
    bool repeat_song_ = false;

public:
    Model(const std::string& musicPath, const std::string& adsPath);

    void add(IPlaybackListener& listener);
    void play(int index);
    void advance();
    void retreat();
    void end();
    void skip();
    void repeat();
    void insert(const std::string& filePath);
    void remove(int index);
    void sort(bool byName);
    void accept(IPlaylistVisitor& visitor) const;
    void search(const std::string& query, IPlaylistVisitor& visitor) const;

private:
    bool validate(const std::string& filePath) const;
    void broadcast() const;
    void refresh() const;
    void resume() const;
};

#endif //MODEL_H