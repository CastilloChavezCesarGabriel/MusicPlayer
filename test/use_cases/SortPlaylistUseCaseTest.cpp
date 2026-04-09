#include "SortPlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include "model/arrangement/QuickSort.h"
#include "model/arrangement/DurationSort.h"
#include <filesystem>
#include <fstream>

std::string SortPlaylistUseCaseTest::identify() const {
    return "sort_uc";
}

TEST_F(SortPlaylistUseCaseTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNameOrdersAlphabetically) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "apple.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "banana.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "cherry.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistDoesNotCrash) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistNotifiesChanged) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongDoesNotCrash) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongPreserves) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("only.mp3"));
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesAllSongNames) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayFirstSong) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlaySelectsCorrectIndex) {
    createSong("c.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenRetreat) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(1);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesDoesNotCrash) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesNotifiesEachTime) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    DurationSort byDuration;
    musicPlayer.sort(byTitle);
    musicPlayer.sort(byDuration);
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChangedTimes(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAlreadySortedPreservesOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterInsert) {
    createSong("c.mp3");
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/b.mp3");
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterRemove) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.remove(1);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameThenByNumber) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameTwoSongs) {
    createSong("z.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "z.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortFiveSongsByName) {
    createSong("e.mp3");
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("d.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(3, "d.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(4, "e.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortThenAcceptVisitsAll) {
    createSong("b.mp3");
    createSong("a.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_FALSE(visitor.isEmpty());
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotAffectPlayback) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotSelect) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayThenAdvanceThroughAll) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    musicPlayer.advance();
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(SortPlaylistUseCaseTest, SortWavFiles) {
    createSong("b.wav");
    createSong("a.wav");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.wav"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.wav"));
}

TEST_F(SortPlaylistUseCaseTest, SortMixedExtensions) {
    createSong("b.wav");
    createSong("a.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongNotifiesChanged) {
    createSong("only.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChangedTimes(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenSearchFindsCorrectly) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("apple", visitor);
    EXPECT_TRUE(visitor.hasName("apple.mp3"));
}
