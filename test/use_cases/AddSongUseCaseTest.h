#ifndef ADD_SONG_USE_CASE_TEST_H
#define ADD_SONG_USE_CASE_TEST_H

#include <gtest/gtest.h>
#include "../MockPlaybackListener.h"
#include <string>

class AddSongUseCaseTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
    std::string externalFile(const std::string& name) const;
};

#endif //ADD_SONG_USE_CASE_TEST_H