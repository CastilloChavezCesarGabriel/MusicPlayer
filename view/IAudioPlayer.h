#ifndef I_AUDIO_PLAYER_H
#define I_AUDIO_PLAYER_H
#include <string>

class IAudioPlayer {
public:
    virtual ~IAudioPlayer() = default;
    virtual void play(const std::string& path) = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void adjust(double volume) = 0;
};

#endif //I_AUDIO_PLAYER_H