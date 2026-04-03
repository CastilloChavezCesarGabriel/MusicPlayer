#ifndef SORT_PLAYLIST_USE_CASE_TEST_H
#define SORT_PLAYLIST_USE_CASE_TEST_H

#include <gtest/gtest.h>
#include "../../model/Model.h"
#include "../MockPlaybackListener.h"
#include <string>

class SortPlaylistUseCaseTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
};

#endif //SORT_PLAYLIST_USE_CASE_TEST_H
