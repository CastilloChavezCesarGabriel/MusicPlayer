#ifndef NAVIGATE_PLAYLIST_USE_CASE_TEST_H
#define NAVIGATE_PLAYLIST_USE_CASE_TEST_H

#include "../ModelTestFixture.h"

class NavigatePlaylistUseCaseTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif //NAVIGATE_PLAYLIST_USE_CASE_TEST_H