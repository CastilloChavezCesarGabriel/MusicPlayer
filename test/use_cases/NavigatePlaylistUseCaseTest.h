#ifndef NAVIGATE_PLAYLIST_USE_CASE_TEST_H
#define NAVIGATE_PLAYLIST_USE_CASE_TEST_H

#include <gtest/gtest.h>
#include "../../model/Model.h"
#include "../MockPlaybackListener.h"
#include <string>

class NavigatePlaylistUseCaseTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
};

#endif //NAVIGATE_PLAYLIST_USE_CASE_TEST_H
