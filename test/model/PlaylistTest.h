#ifndef PLAYLISTTEST_H
#define PLAYLISTTEST_H

#include <gtest/gtest.h>
#include "../../model/Playlist.h"
#include "../../model/MusicLibrary.h"
#include "../TestPlaylistVisitor.h"
#include "../MockPlaybackListener.h"
#include <string>

class PlaylistTest : public ::testing::Test {
protected:
    std::string test_directory_;
    MusicLibrary*library_ = nullptr;
    Playlist*playlist_ = nullptr;
    TestPlaylistVisitor visitor_;
    MockPlaybackListener listener_;

    void SetUp() override;
    void TearDown() override;
    void populate(int count) const;
};

#endif