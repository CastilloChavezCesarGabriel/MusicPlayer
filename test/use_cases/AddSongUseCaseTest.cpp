#include "AddSongUseCaseTest.h"
#include "../../model/Model.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

void AddSongUseCaseTest::SetUp() {
    baseDir = std::filesystem::temp_directory_path().string() + "/add_uc";
    musicDir = baseDir + "/music";
    adsDir = baseDir + "/ads";
    std::filesystem::create_directories(musicDir);
    std::filesystem::create_directories(adsDir);
}

void AddSongUseCaseTest::TearDown() {
    std::filesystem::remove_all(baseDir);
}

void AddSongUseCaseTest::createSong(const std::string& name) const {
    std::ofstream(musicDir + "/" + name) << "audio";
}

std::string AddSongUseCaseTest::externalFile(const std::string& name) const {
    std::string srcDir = baseDir + "/src";
    std::filesystem::create_directories(srcDir);
    std::string path = srcDir + "/" + name;
    std::ofstream(path) << "audio";
    return path;
}

TEST_F(AddSongUseCaseTest, AddValidMp3GivesSuccessFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.wav");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.txt");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert("");
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("This song already exists."));
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("my_track.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("my_track.mp3"));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string p1 = externalFile("a.mp3");
    model.insert(p1);
    std::string p2 = externalFile("b.mp3");
    model.insert(p2);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string p1 = externalFile("a.mp3");
    model.insert(p1);
    std::string p2 = externalFile("b.mp3");
    model.insert(p2);
    EXPECT_TRUE(listener.wasChangedTimes(2));
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.remove(0);
    std::string path = externalFile("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("a.mp3");
    model.insert(path);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("unique.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.search("unique", visitor);
    EXPECT_TRUE(visitor.hasName("unique.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    model.play(0);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener.wasStarted());
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.ogg");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.flac");
    model.insert(path);
    EXPECT_TRUE(listener.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.txt");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.txt");
    model.insert(path);
    EXPECT_FALSE(listener.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("existing.mp3"));
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert("");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(externalFile("a.mp3"));
    model.insert(externalFile("b.mp3"));
    model.insert(externalFile("c.mp3"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(externalFile("a.mp3"));
    model.remove(0);
    model.insert(externalFile("b.mp3"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(externalFile("track.wav"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(externalFile("zebra.mp3"));
    model.insert(externalFile("alpha.mp3"));
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.search("alpha", visitor);
    EXPECT_TRUE(visitor.hasName("alpha.mp3"));
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    std::string path = externalFile("song.mp3");
    EXPECT_NO_THROW(model.insert(path));
}