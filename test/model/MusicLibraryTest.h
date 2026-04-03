#ifndef MUSICLIBRARYTEST_H
#define MUSICLIBRARYTEST_H

#include <gtest/gtest.h>
#include "../../model/MusicLibrary.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <string>

class MusicLibraryTest : public ::testing::Test {
protected:
    std::string testDir;

    void SetUp() override;
    void TearDown() override;
    void createFile(const std::string& name);
};

#endif
