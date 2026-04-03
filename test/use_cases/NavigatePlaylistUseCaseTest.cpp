#include "NavigatePlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

void NavigatePlaylistUseCaseTest::SetUp() {
    baseDir = std::filesystem::temp_directory_path().string() + "/navigate_uc";
    musicDir = baseDir + "/music";
    adsDir = baseDir + "/ads";
    std::filesystem::create_directories(musicDir);
    std::filesystem::create_directories(adsDir);
}

void NavigatePlaylistUseCaseTest::TearDown() {
    std::filesystem::remove_all(baseDir);
}

void NavigatePlaylistUseCaseTest::createSong(const std::string& name) const {
    std::ofstream(musicDir + "/" + name) << "audio";
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromLastToMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(2);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatFromMiddleToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatReturnsToStart) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatThroughAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(2);
    model.retreat();
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatNotifiesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    model.play(2);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.remove(0);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.remove(0);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = baseDir + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(srcDir + "/b.mp3");
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = baseDir + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(srcDir + "/b.mp3");
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    model.advance();
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(3));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(3);
    model.retreat();
    model.retreat();
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenRetreatThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    model.retreat();
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.advance());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatOnSingleSongDoesNotCrash) {
    createSong("only.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.retreat());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatTwoSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    model.advance();
    model.advance();
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(4));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_FALSE(listener.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatDoesNotNotifyChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_FALSE(listener.wasChanged());
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceThenPlaylistUnchanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(NavigatePlaylistUseCaseTest, AdvanceSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    model.play(0);
    model.advance();
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(2));
}

TEST_F(NavigatePlaylistUseCaseTest, RetreatSortedPlaylist) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    model.play(2);
    model.retreat();
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}
