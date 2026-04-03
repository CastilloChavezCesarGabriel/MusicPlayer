#ifndef SEARCH_SONG_USE_CASE_TEST_H
#define SEARCH_SONG_USE_CASE_TEST_H

#include <gtest/gtest.h>
#include "../../model/Model.h"
#include "../MockPlaybackListener.h"
#include <string>

class SearchSongUseCaseTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
};

#endif //SEARCH_SONG_USE_CASE_TEST_H
