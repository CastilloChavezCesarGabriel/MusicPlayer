#include "SortPlaylistUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string SortPlaylistUseCaseTest::identify() const {
    return "sort_uc";
}

TEST_F(SortPlaylistUseCaseTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(false);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortByNameOrdersAlphabetically) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "apple.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "banana.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "cherry.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistDoesNotCrash) {
    Model model(base_directory_);
    model.subscribe(listener_);
    EXPECT_NO_THROW(model.sort(true));
}

TEST_F(SortPlaylistUseCaseTest, SortEmptyPlaylistNotifiesChanged) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongDoesNotCrash) {
    createSong("only.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    EXPECT_NO_THROW(model.sort(true));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongPreserves) {
    createSong("only.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("only.mp3"));
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortPreservesAllSongNames) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayFirstSong) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlaySelectsCorrectIndex) {
    createSong("c.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortThenAdvance) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenRetreat) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesDoesNotCrash) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    EXPECT_NO_THROW(model.sort(true));
    EXPECT_NO_THROW(model.sort(false));
    EXPECT_NO_THROW(model.sort(true));
}

TEST_F(SortPlaylistUseCaseTest, SortMultipleTimesNotifiesEachTime) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.sort(false);
    model.sort(true);
    EXPECT_TRUE(listener_.wasChangedTimes(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAlreadySortedPreservesOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    EXPECT_NO_THROW(model.sort(false));
}

TEST_F(SortPlaylistUseCaseTest, SortByNumberPreservesSongCount) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(false);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterInsert) {
    createSong("c.mp3");
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert(srcDir + "/b.mp3");
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortAfterRemove) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(1);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameThenByNumber) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.sort(false);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortByNameTwoSongs) {
    createSong("z.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "z.mp3"));
}

TEST_F(SortPlaylistUseCaseTest, SortFiveSongsByName) {
    createSong("e.mp3");
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("d.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
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
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_FALSE(visitor.isEmpty());
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotAffectPlayback) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(SortPlaylistUseCaseTest, SortDoesNotSelect) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(SortPlaylistUseCaseTest, SortThenPlayThenAdvanceThroughAll) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.play(0);
    model.advance();
    model.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(2));
}

TEST_F(SortPlaylistUseCaseTest, SortWavFiles) {
    createSong("b.wav");
    createSong("a.wav");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.wav"));
    EXPECT_TRUE(visitor.hasNameAt(1, "b.wav"));
}

TEST_F(SortPlaylistUseCaseTest, SortMixedExtensions) {
    createSong("b.wav");
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SortPlaylistUseCaseTest, SortSingleSongNotifiesChanged) {
    createSong("only.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    EXPECT_TRUE(listener_.wasChangedTimes(1));
}

TEST_F(SortPlaylistUseCaseTest, SortThenSearchFindsCorrectly) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.search("apple", visitor);
    EXPECT_TRUE(visitor.hasName("apple.mp3"));
}
