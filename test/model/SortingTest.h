#ifndef SORTINGTEST_H
#define SORTINGTEST_H

#include <gtest/gtest.h>
#include "../../model/ShellSort.h"
#include "../../model/QuickSort.h"
#include "../../model/Song.h"
#include "../TestPlaylistVisitor.h"
#include <vector>
#include <string>

class ShellSortTest : public ::testing::Test {
protected:
    ShellSort sorter_;
    TestPlaylistVisitor visitor_;

    void verify(std::vector<Song>& songs, const std::vector<std::string>& expected);
};

class QuickSortTest : public ::testing::Test {
protected:
    QuickSort sorter_;
    TestPlaylistVisitor visitor_;
};

#endif