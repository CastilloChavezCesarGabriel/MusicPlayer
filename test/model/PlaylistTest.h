#ifndef PLAYLISTTEST_H
#define PLAYLISTTEST_H

#include <gtest/gtest.h>
#include "../../model/Playlist.h"
#include "../../model/MusicLibrary.h"
#include "../../model/ShellSort.h"
#include "../../model/QuickSort.h"
#include "../../model/IPlaybackListener.h"
#include "../TestPlaylistVisitor.h"
#include "../MockPlaybackListener.h"
#include <filesystem>
#include <string>

class PlaylistTest : public ::testing::Test {
protected:
    std::string testDir;
    MusicLibrary* library;
    Playlist* playlist;
    TestPlaylistVisitor visitor;
    MockPlaybackListener listener;

    void SetUp() override;
    void TearDown() override;
    void populate(int count);
};

#endif
