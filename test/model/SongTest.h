#ifndef SONGTEST_H
#define SONGTEST_H

#include <gtest/gtest.h>
#include "../TestPlaylistVisitor.h"

class SongTest : public ::testing::Test {
protected:
    TestPlaylistVisitor visitor_;
};

#endif