#ifndef ADD_SONG_USE_CASE_TEST_H
#define ADD_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class AddSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
    std::string prepare(const std::string& name) const;
};

#endif //ADD_SONG_USE_CASE_TEST_H