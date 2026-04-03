#ifndef MODELTEST_H
#define MODELTEST_H

#include <gtest/gtest.h>
#include "../../model/Model.h"
#include "../MockPlaybackListener.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <string>

class ModelTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name);
    void createAd(const std::string& name);
    Model createModel();
};

#endif
