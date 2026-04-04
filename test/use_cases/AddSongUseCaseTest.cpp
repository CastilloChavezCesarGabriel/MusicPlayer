#include "AddSongUseCaseTest.h"
#include "../../model/Model.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string AddSongUseCaseTest::identify() const {
    return "add_uc";
}

std::string AddSongUseCaseTest::prepare(const std::string& name) const {
    const std::string src_directory_ = base_directory_ + "/src";
    std::filesystem::create_directories(src_directory_);
    std::string path = src_directory_ + "/" + name;
    std::ofstream(path) << "audio";
    return path;
}

TEST_F(AddSongUseCaseTest, AddValidMp3GivesSuccessFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.wav");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.txt");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("my_track.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("my_track.mp3"));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    model.insert(p1);
    std::string p2 = prepare("b.mp3");
    model.insert(p2);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    model.insert(p1);
    std::string p2 = prepare("b.mp3");
    model.insert(p2);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    model.remove(0);
    std::string path = prepare("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("a.mp3");
    model.insert(path);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("unique.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.search("unique", visitor);
    EXPECT_TRUE(visitor.hasName("unique.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    model.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.ogg");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.flac");
    model.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.txt");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.txt");
    model.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    model.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("new.mp3");
    model.insert(path);
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasName("existing.mp3"));
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert("");
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert(prepare("a.mp3"));
    model.insert(prepare("b.mp3"));
    model.insert(prepare("c.mp3"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert(prepare("a.mp3"));
    model.remove(0);
    model.insert(prepare("b.mp3"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert(prepare("track.wav"));
    TestPlaylistVisitor visitor;
    model.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    Model model(base_directory_);
    model.subscribe(listener_);
    model.insert(prepare("zebra.mp3"));
    model.insert(prepare("alpha.mp3"));
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.search("alpha", visitor);
    EXPECT_TRUE(visitor.hasName("alpha.mp3"));
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    Model model(base_directory_);
    model.subscribe(listener_);
    std::string path = prepare("song.mp3");
    EXPECT_NO_THROW(model.insert(path));
}