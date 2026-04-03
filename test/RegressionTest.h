#ifndef REGRESSIONTEST_H
#define REGRESSIONTEST_H

#include <gtest/gtest.h>
#include "../model/Song.h"
#include "../model/Playlist.h"
#include "../model/MusicLibrary.h"
#include "../model/Model.h"
#include "../model/ShellSort.h"
#include "../model/QuickSort.h"
#include "MockPlaybackListener.h"
#include "TestPlaylistVisitor.h"
#include <filesystem>
#include <string>

class RegressionTest : public ::testing::Test {
protected:
    std::string baseDir;
    std::string musicDir;
    std::string adsDir;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
};

#endif
