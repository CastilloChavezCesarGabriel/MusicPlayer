#include "ModelTest.h"
#include <fstream>

void ModelTest::SetUp() {
    baseDir = std::filesystem::temp_directory_path().string() + "/model_test";
    musicDir = baseDir + "/music";
    adsDir = baseDir + "/ads";
    std::filesystem::create_directories(musicDir);
    std::filesystem::create_directories(adsDir);
}

void ModelTest::TearDown() {
    std::filesystem::remove_all(baseDir);
}

void ModelTest::createSong(const std::string& name) {
    std::ofstream(musicDir + "/" + name) << "audio";
}

void ModelTest::createAd(const std::string& name) {
    std::ofstream(adsDir + "/" + name) << "ad";
}

Model ModelTest::createModel() {
    return Model(musicDir, adsDir);
}

TEST_F(ModelTest, LoadsSongsFromDirectory) {
    createSong("(1) First.mp3");
    createSong("(2) Second.mp3");
    Model model = createModel();
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, LoadsEmptyDirectory) {
    Model model = createModel();
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, PlaySelectsAndStartsSong) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(ModelTest, PlayNotifiesSelection) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.play(0);
    EXPECT_TRUE(listener.wasSelectedWith(0));
}

TEST_F(ModelTest, AdvanceMovesToNextSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = createModel();
    model.add(listener);
    model.play(0);
    model.advance();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(ModelTest, RetreatMovesToPreviousSong) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = createModel();
    model.add(listener);
    model.play(2);
    model.retreat();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(ModelTest, RepeatNotifiesFeedback) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.repeat();
    EXPECT_TRUE(listener.wasFeedback("Repeat enabled"));
}

TEST_F(ModelTest, RepeatToggle) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.repeat();
    model.repeat();
    EXPECT_TRUE(listener.wasFeedback("Repeat disabled"));
}

TEST_F(ModelTest, InsertValidFile) {
    std::string srcDir = baseDir + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    Model model = createModel();
    model.add(listener);
    model.insert(srcDir + "/new.mp3");
    EXPECT_TRUE(listener.wasChanged());
    EXPECT_TRUE(listener.wasFeedback("Song added successfully!"));
}

TEST_F(ModelTest, InsertUnsupportedFile) {
    std::string srcDir = baseDir + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/doc.txt") << "text";

    Model model = createModel();
    model.add(listener);
    model.insert(srcDir + "/doc.txt");
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertEmptyPath) {
    Model model = createModel();
    model.add(listener);
    model.insert("");
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(ModelTest, InsertDuplicateFile) {
    createSong("existing.mp3");
    std::string srcDir = baseDir + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "audio";

    Model model = createModel();
    model.add(listener);
    model.insert(srcDir + "/existing.mp3");
    EXPECT_TRUE(listener.wasFeedback("This song already exists."));
}

TEST_F(ModelTest, RemoveNotifiesChanged) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.remove(0);
    EXPECT_TRUE(listener.wasChanged());
}

TEST_F(ModelTest, RemoveReducesPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model = createModel();
    model.add(listener);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameNotifiesChanged) {
    createSong("b.mp3");
    createSong("a.mp3");
    Model model = createModel();
    model.add(listener);
    model.sort(true);
    EXPECT_TRUE(listener.wasChanged());
}

TEST_F(ModelTest, SortByNumberNotifiesChanged) {
    createSong("(2) B.mp3");
    createSong("(1) A.mp3");
    Model model = createModel();
    model.add(listener);
    model.sort(false);
    EXPECT_TRUE(listener.wasChanged());
}

TEST_F(ModelTest, SearchFiltersSongs) {
    createSong("Hello.mp3");
    createSong("Goodbye.mp3");
    createSong("Hello World.mp3");
    Model model = createModel();
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(ModelTest, SearchNoResults) {
    createSong("Hello.mp3");
    Model model = createModel();
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("ZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(ModelTest, AcceptShowsAllSongs) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = createModel();
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(ModelTest, EndWithoutAdAdvances) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model = createModel();
    model.add(listener);
    model.play(0);
    model.end();
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(ModelTest, SkipWithoutAdDoesNothing) {
    createSong("song.mp3");
    Model model = createModel();
    model.add(listener);
    model.skip();
    EXPECT_FALSE(listener.wasRevealed());
}

TEST_F(ModelTest, InsertIncreasesPlaylistSize) {
    std::string srcDir = baseDir + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "audio";

    Model model = createModel();
    model.add(listener);
    model.insert(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, SortByNameOrders) {
    createSong("C.mp3");
    createSong("A.mp3");
    createSong("B.mp3");
    Model model = createModel();
    model.add(listener);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(ModelTest, MultipleRemoves) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    Model model = createModel();
    model.add(listener);
    model.remove(0);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(ModelTest, MultipleInserts) {
    std::string srcDir = baseDir + "/import";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/a.mp3") << "audio";
    std::ofstream(srcDir + "/b.mp3") << "audio";

    Model model = createModel();
    model.add(listener);
    model.insert(srcDir + "/a.mp3");
    model.insert(srcDir + "/b.mp3");
    EXPECT_TRUE(listener.wasChangedTimes(2));
}
