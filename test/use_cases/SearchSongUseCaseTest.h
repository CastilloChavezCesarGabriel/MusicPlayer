#ifndef SEARCH_SONG_USE_CASE_TEST_H
#define SEARCH_SONG_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class SearchSongUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //SEARCH_SONG_USE_CASE_TEST_H