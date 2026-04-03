#include "ModelTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string ModelTest::identify() const {
    return "model_test";
}

Model ModelTest::create() const {
    return Model(music_directory_, ads_directory_);
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    Model model = create();
    model.add(listener_);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    Model model = create();
    model.add(listener_);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelectedWith(0));
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = create();
    model.add(listener_);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = create();
    model.add(listener_);
    model.play(2);
    model.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, RepeatNotifiesFeedback) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.repeat();
    EXPECT_TRUE(listener_.wasFeedback("Repeat enabled"));
}

TEST_F(ModelTest, RepeatToggle) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.repeat();
    model.repeat();
    EXPECT_TRUE(listener_.wasFeedback("Repeat disabled"));
}

TEST_F(ModelTest, InsertValidFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    Model model = create();
    model.add(listener_);
    model.insert(srcDir + "/new.mp3");
    EXPECT_TRUE(listener_.wasChanged());
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/doc.txt") << "text";

    Model model = create();
    model.add(listener_);
    model.insert(srcDir + "/doc.txt");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertEmptyPath) {
    Model model = create();
    model.add(listener_);
    model.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "audio";

    Model model = create();
    model.add(listener_);
    model.insert(srcDir + "/existing.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.remove(0);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model = create();
    model.add(listener_);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model = create();
    model.add(listener_);
    model.sort(true);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    Model model = create();
    model.add(listener_);
    model.sort(false);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    Model model = create();
    model.add(listener_);
    TestPlaylistVisitor visitor;
    model.search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    Model model = create();
    model.add(listener_);
    TestPlaylistVisitor visitor;
    model.search("ZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = create();
    model.add(listener_);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model = create();
    model.add(listener_);
    model.play(0);
    model.end();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    Model model = create();
    model.add(listener_);
    model.skip();
    EXPECT_FALSE(listener_.wasRevealed());
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    Model model = create();
    model.add(listener_);
    model.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    Model model = create();
    model.add(listener_);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(ModelTest, MultipleRemoves) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = create();
    model.add(listener_);
    model.remove(0);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, MultipleInserts) {
    std::string srcDir = base_directory_ + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/a.mp3") << "audio";
    std::ofstream(srcDir + "/b.mp3") << "audio";

    Model model = create();
    model.add(listener_);
    model.insert(srcDir + "/a.mp3");
    model.insert(srcDir + "/b.mp3");
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}