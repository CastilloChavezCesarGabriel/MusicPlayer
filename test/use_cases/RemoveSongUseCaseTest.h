#ifndef REMOVE_SONG_USE_CASE_TEST_H
#define REMOVE_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class RemoveSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //REMOVE_SONG_USE_CASE_TEST_H