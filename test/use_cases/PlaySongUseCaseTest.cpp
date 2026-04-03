#include "PlaySongUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

void PlaySongUseCaseTest::SetUp() {
    baseDir = std::filesystem::temp_directory_path().string() + "/play_uc";
    musicDir = baseDir + "/music";
    adsDir = baseDir + "/ads";
    std::filesystem::create_directories(musicDir);
    std::filesystem::create_directories(adsDir);
}

void PlaySongUseCaseTest::TearDown() {
    std::filesystem::remove_all(baseDir);
}

void PlaySongUseCaseTest::createSong(const std::string& name) const {
    std::ofstream(musicDir + "/" + name) << "audio";
}

void PlaySongUseCaseTest::createAd(const std::string& name) const {
    std::ofstream(adsDir + "/" + name) << "ad";
}

TEST_F(PlaySongUseCaseTest, PlaySelectsSong) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, PlayStartsPlayback) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlaySecondSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayThenPlayAnother) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.play(1);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(2);
    EXPECT_TRUE(listener.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(2);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAlwaysSelects) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayMultipleTimesAllSelect) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.play(1);
    model.play(0);
    EXPECT_TRUE(listener.wasSelectedWith(0));
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAdvancesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.end();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAtLastSongDoesNotCrash) {
    createSong("a.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.end());
}

TEST_F(PlaySongUseCaseTest, RepeatEnablesFeedback) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.repeat();
    EXPECT_TRUE(listener.wasFeedback("Repeat enabled"));
}

TEST_F(PlaySongUseCaseTest, RepeatDisablesFeedback) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.repeat();
    model.repeat();
    EXPECT_TRUE(listener.wasFeedback("Repeat disabled"));
}

TEST_F(PlaySongUseCaseTest, EndWithRepeatReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.repeat();
    model.play(0);
    model.end();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.skip();
    EXPECT_FALSE(listener.wasRevealed());
}

TEST_F(PlaySongUseCaseTest, PlayWithSingleSong) {
    createSong("only.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayDoesNotCrashOnEmptyPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    EXPECT_NO_THROW(model.play(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, RetreatFromSecondToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThroughEntirePlaylist) {
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

TEST_F(PlaySongUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.retreat());
}

TEST_F(PlaySongUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_NO_THROW(model.advance());
}

TEST_F(PlaySongUseCaseTest, PlaySortedThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, EndMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    model.end();
    model.end();
    EXPECT_TRUE(listener.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.remove(0);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAfterInsert) {
    std::string srcDir = baseDir + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(srcDir + "/new.mp3");
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThenRetreat) {
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

TEST_F(PlaySongUseCaseTest, PlayAfterShuffle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RepeatToggleMultipleTimes) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.repeat();
    model.repeat();
    model.repeat();
    EXPECT_TRUE(listener.wasFeedback("Repeat enabled"));
    EXPECT_TRUE(listener.wasFeedback("Repeat disabled"));
}
