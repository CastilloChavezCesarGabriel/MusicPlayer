#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include <gtest/gtest.h>
#include "../../model/Advertisement.h"
#include "../MockPlaybackListener.h"
#include <filesystem>
#include <string>

class AdvertisementTest : public ::testing::Test {
protected:
    std::string testDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createAdFile(const std::string& name);
};

#endif
