#include "PlaySongUseCaseTest.h"
#include "model/arrangement/QuickSort.h"
#include <filesystem>
#include <fstream>

std::string PlaySongUseCaseTest::identify() const {
    return "play_uc";
}

TEST_F(PlaySongUseCaseTest, PlaySelectsSong) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, PlayStartsPlayback) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlaySecondSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayThenPlayAnother) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.play(1);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, PlayLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayFromMiddle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAlwaysSelects) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayMultipleTimesAllSelect) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.play(1);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAdvancesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, EndAtLastSongDoesNotCrash) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.end());
}

TEST_F(PlaySongUseCaseTest, RepeatOneReplays) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(PlaySongUseCaseTest, RepeatAllLoops) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, EndWithRepeatReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(PlaySongUseCaseTest, PlayWithSingleSong) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayDoesNotCrashOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    EXPECT_NO_THROW(musicPlayer.play(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceFromFirstToSecond) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaySongUseCaseTest, RetreatFromSecondToFirst) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, AdvanceStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RetreatStartsPlayback) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThroughEntirePlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, RetreatAtStartDoesNotCrash) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.retreat());
}

TEST_F(PlaySongUseCaseTest, AdvanceAtEndDoesNotCrash) {
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(PlaySongUseCaseTest, PlaySortedThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, EndMultipleTimes) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(PlaySongUseCaseTest, PlayAfterRemove) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, PlayAfterInsert) {
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, AdvanceThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(PlaySongUseCaseTest, PlayAfterShuffle) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaySongUseCaseTest, RepeatOffAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}