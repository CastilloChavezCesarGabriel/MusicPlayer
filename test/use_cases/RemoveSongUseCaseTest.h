#ifndef REMOVE_SONG_USE_CASE_TEST_H
#define REMOVE_SONG_USE_CASE_TEST_H

#include <gtest/gtest.h>
#include "../../model/Model.h"
#include "../MockPlaybackListener.h"
#include <string>

class RemoveSongUseCaseTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
};

#endif //REMOVE_SONG_USE_CASE_TEST_H
