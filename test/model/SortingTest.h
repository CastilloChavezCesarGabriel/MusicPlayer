#ifndef SORTINGTEST_H
#define SORTINGTEST_H

#include <gtest/gtest.h>
#include "model/arrangement/DurationSort.h"
#include "model/arrangement/QuickSort.h"
#include "model/core/Song.h"
#include "../TestPlaylistVisitor.h"
#include <vector>
#include <string>

class ShellSortTest : public ::testing::Test {
protected:
    std::string test_directory_;
    DurationSort sorter_;
    TestPlaylistVisitor visitor_;

    void SetUp() override;
    void TearDown() override;
    std::string createFile(const std::string& name, int size) const;
};

class QuickSortTest : public ::testing::Test {
protected:
    QuickSort sorter_;
    TestPlaylistVisitor visitor_;
};

#endif