#include "ModelTest.h"
#include "../TestPlaylistVisitor.h"
#include "../../model/QuickSort.h"
#include "../../model/DurationSort.h"
#include "../../model/DateSort.h"
#include <filesystem>
#include <fstream>

std::string ModelTest::identify() const {
    return "model_test";
}

MusicPlayer ModelTest::create() {
    return MusicPlayer(base_directory_, dice_);
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RepeatOneReplays) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(ModelTest, RepeatAllLoops) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, InsertValidFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    EXPECT_TRUE(listener_.wasChanged());
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/doc.txt") << "text";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/doc.txt");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertEmptyPath) {
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/existing.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    musicPlayer.sort(byDuration);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.search("ZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(ModelTest, MultipleRemoves) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    musicPlayer.remove(0);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, MultipleInserts) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/a.mp3") << "audio";
    std::ofstream(srcDir + "/b.mp3") << "audio";

    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/a.mp3");
    musicPlayer.insert(srcDir + "/b.mp3");
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(ModelTest, ReverseNotifiesChanged) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    musicPlayer.reverse();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, ReverseInvertsOrder) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byName;
    musicPlayer.sort(byName);
    musicPlayer.reverse();
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "c.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "a.mp3"));
}

TEST_F(ModelTest, RestoreNotifiesChanged) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    QuickSort byName;
    musicPlayer.sort(byName);
    musicPlayer.restore();
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateNotifiesChanged) {
    createSong("a.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DateSort byDate;
    musicPlayer.sort(byDate);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByDateAcceptsSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer = create();
    musicPlayer.subscribe(listener_);
    DateSort byDate;
    musicPlayer.sort(byDate);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}