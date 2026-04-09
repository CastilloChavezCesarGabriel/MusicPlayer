#include "AddSongUseCaseTest.h"
#include "model/MusicPlayer.h"
#include "model/arrangement/QuickSort.h"
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
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddValidWavGivesSuccessFeedback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.wav");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Song added successfully!"));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedTypeGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddDuplicateGivesFeedback) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(AddSongUseCaseTest, AddIncreasesPlaylistSize) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddNotifiesChanged) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddSongAppearsInPlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("my_track.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("my_track.mp3"));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongs) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    musicPlayer.insert(p1);
    std::string p2 = prepare("b.mp3");
    musicPlayer.insert(p2);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddMultipleSongsNotifiesMultipleTimes) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string p1 = prepare("a.mp3");
    musicPlayer.insert(p1);
    std::string p2 = prepare("b.mp3");
    musicPlayer.insert(p2);
    EXPECT_TRUE(listener_.wasChangedTimes(2));
}

TEST_F(AddSongUseCaseTest, AddAfterRemove) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.remove(0);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSort) {
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("a.mp3");
    musicPlayer.insert(path);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "a.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenSearch) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("unique.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.search("unique", visitor);
    EXPECT_TRUE(visitor.hasName("unique.mp3"));
}

TEST_F(AddSongUseCaseTest, AddThenPlayNewSong) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    musicPlayer.play(0);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddDoesNotStartPlayback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AddSongUseCaseTest, AddDoesNotSelect) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasSelected());
}

TEST_F(AddSongUseCaseTest, AddOggGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.ogg");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddFlacGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.flac");
    musicPlayer.insert(path);
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotIncreasePlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddUnsupportedDoesNotNotifyChanged) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.txt");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotIncreasePlaylist) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddDuplicateDoesNotNotifyChanged) {
    createSong("song.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    musicPlayer.insert(path);
    EXPECT_FALSE(listener_.wasChanged());
}

TEST_F(AddSongUseCaseTest, AddToExistingPlaylist) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(AddSongUseCaseTest, AddPreservesExistingSongs) {
    createSong("existing.mp3");
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("new.mp3");
    musicPlayer.insert(path);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasName("existing.mp3"));
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(AddSongUseCaseTest, AddEmptyPathDoesNotIncreasePlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(AddSongUseCaseTest, AddThreeSongsSequentially) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("a.mp3"));
    musicPlayer.insert(prepare("b.mp3"));
    musicPlayer.insert(prepare("c.mp3"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(AddSongUseCaseTest, AddThenRemoveThenAdd) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("a.mp3"));
    musicPlayer.remove(0);
    musicPlayer.insert(prepare("b.mp3"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(AddSongUseCaseTest, AddWavIncreasesPlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("track.wav"));
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(AddSongUseCaseTest, AddThenSortThenSearch) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(prepare("zebra.mp3"));
    musicPlayer.insert(prepare("alpha.mp3"));
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.search("alpha", visitor);
    EXPECT_TRUE(visitor.hasName("alpha.mp3"));
}

TEST_F(AddSongUseCaseTest, AddDoesNotCrashOnEmptyPlaylist) {
    MusicPlayer musicPlayer(base_directory_, ad_policy_);
    musicPlayer.subscribe(listener_);
    std::string path = prepare("song.mp3");
    EXPECT_NO_THROW(musicPlayer.insert(path));
}