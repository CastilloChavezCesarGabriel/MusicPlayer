#include "RemoveSongUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string RemoveSongUseCaseTest::identify() const {
    return "remove_uc";
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveLastSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(2);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveMiddleSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(1);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChanged) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(RemoveSongUseCaseTest, RemoveReducesPlaylistSize) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveFromEmptyDoesNotCrash) {
    Model model(base_directory_);
    model.subscribe(listener_);
    EXPECT_NO_THROW(model.remove(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlay) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(RemoveSongUseCaseTest, RemoveOnlySongLeavesEmpty) {
    createSong("only.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveAllSongsOneByOne) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.remove(0);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdd) {
    createSong("a.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.insert(srcDir + "/b.mp3");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSort) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearch) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.search("jazz", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotStartPlayback) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotSelect) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(RemoveSongUseCaseTest, RemoveMultipleNotifiesEachTime) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(RemoveSongUseCaseTest, RemovePreservesOtherSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(1);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
    EXPECT_TRUE(visitor.hasName("c.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveFirstPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveLastPreservesRest) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(1);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenPlayRemaining) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenAdvance) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenRetreat) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.play(1);
    model.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(RemoveSongUseCaseTest, RemoveAllThenAddNew) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";
    model.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveTwoFromThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSortRemaining) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "b.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "c.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveWavFile) {
    createSong("track.wav");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(RemoveSongUseCaseTest, RemoveNotifiesChangedOnce) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(1));
}

TEST_F(RemoveSongUseCaseTest, RemoveFromFiveSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    createSong("d.mp3");
    createSong("e.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(2);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(4));
}

TEST_F(RemoveSongUseCaseTest, RemoveThreeTimesNotifiesThree) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    model.remove(0);
    model.remove(0);
    EXPECT_TRUE(listener_.wasChangedTimes(3));
}

TEST_F(RemoveSongUseCaseTest, RemoveThenSearchFindsRemaining) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.sort(true);
    model.remove(1);
    TestPlaylistVisitor visitor;
    model.search("jazz", visitor);
    EXPECT_TRUE(visitor.hasName("jazz.mp3"));
}

TEST_F(RemoveSongUseCaseTest, RemoveDoesNotGiveFeedback) {
    createSong("a.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    EXPECT_FALSE(listener_.wasFeedback("Song added successfully!"));
}