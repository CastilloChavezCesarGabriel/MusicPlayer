#ifndef MODEL_TEST_FIXTURE_H
#define MODEL_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../model/Model.h"
#include "MockPlaybackListener.h"
#include "TestPlaylistVisitor.h"
#include <string>

class ModelTestFixture : public ::testing::Test {
protected:
    std::string base_directory_;
    std::string music_directory_;
    std::string ads_directory_;
    MockPlaybackListener listener_;

    void SetUp() override;
    void TearDown() override;
    void createSong(const std::string& name) const;
    void createAd(const std::string& name) const;
    virtual std::string identify() const = 0;
};

#endif //MODEL_TEST_FIXTURE_H