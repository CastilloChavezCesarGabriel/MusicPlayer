#ifndef PLAY_SONG_USE_CASE_TEST_H
#define PLAY_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class PlaySongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //PLAY_SONG_USE_CASE_TEST_H