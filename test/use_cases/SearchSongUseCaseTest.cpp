#include "SearchSongUseCaseTest.h"
#include "../TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

void SearchSongUseCaseTest::SetUp() {
    baseDir = std::filesystem::temp_directory_path().string() + "/search_uc";
    musicDir = baseDir + "/music";
    adsDir = baseDir + "/ads";
    std::filesystem::create_directories(musicDir);
    std::filesystem::create_directories(adsDir);
}

void SearchSongUseCaseTest::TearDown() {
    std::filesystem::remove_all(baseDir);
}

void SearchSongUseCaseTest::createSong(const std::string& name) const {
    std::ofstream(musicDir + "/" + name) << "audio";
}

TEST_F(SearchSongUseCaseTest, SearchFindsExactMatch) {
    createSong("hello.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("hello", visitor);
    EXPECT_TRUE(visitor.hasName("hello.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchNoMatchReturnsEmpty) {
    createSong("hello.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("goodbye", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryReturnsAll) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchPartialName) {
    createSong("summer_breeze.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("summer", visitor);
    EXPECT_TRUE(visitor.hasName("summer_breeze.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchMultipleResults) {
    createSong("rock_anthem.mp3");
    createSong("rock_ballad.mp3");
    createSong("jazz_tune.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("rock", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchSingleResult) {
    createSong("rock_anthem.mp3");
    createSong("jazz_tune.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("jazz", visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchOnEmptyPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("anything", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchEmptyQueryOnEmptyPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchAfterSort) {
    createSong("cherry.mp3");
    createSong("apple.mp3");
    createSong("banana.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.search("banana", visitor);
    EXPECT_TRUE(visitor.hasName("banana.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchAfterInsert) {
    createSong("a.mp3");
    std::string srcDir = baseDir + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/b.mp3") << "audio";
    Model model(musicDir, adsDir);
    model.add(listener);
    model.insert(srcDir + "/b.mp3");
    TestPlaylistVisitor visitor;
    model.search("b", visitor);
    EXPECT_TRUE(visitor.hasName("b.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchAfterRemove) {
    createSong("unique_song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.remove(0);
    TestPlaylistVisitor visitor;
    model.search("unique_song", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotStartPlayback) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("song", visitor);
    EXPECT_FALSE(listener.wasStarted());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotSelect) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("song", visitor);
    EXPECT_FALSE(listener.wasSelected());
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotNotifyChanged) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("song", visitor);
    EXPECT_FALSE(listener.wasChanged());
}

TEST_F(SearchSongUseCaseTest, SearchWithExtension) {
    createSong("song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search(".mp3", visitor);
    EXPECT_TRUE(visitor.hasName("song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWavFile) {
    createSong("track.wav");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("track", visitor);
    EXPECT_TRUE(visitor.hasName("track.wav"));
}

TEST_F(SearchSongUseCaseTest, SearchWithUnderscore) {
    createSong("my_song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("my_song", visitor);
    EXPECT_TRUE(visitor.hasName("my_song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWithDash) {
    createSong("my-song.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("my-song", visitor);
    EXPECT_TRUE(visitor.hasName("my-song.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchWithNumbers) {
    createSong("track01.mp3");
    createSong("track02.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("track0", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchSingleCharacter) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("a", visitor);
    EXPECT_TRUE(visitor.hasName("a.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchTwiceWithDifferentQueries) {
    createSong("rock.mp3");
    createSong("jazz.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor v1;
    model.search("rock", v1);
    EXPECT_TRUE(v1.hasName("rock.mp3"));
    TestPlaylistVisitor v2;
    model.search("jazz", v2);
    EXPECT_TRUE(v2.hasName("jazz.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotAffectPlaylist) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor searchVisitor;
    model.search("a", searchVisitor);
    TestPlaylistVisitor acceptVisitor;
    model.accept(acceptVisitor);
    EXPECT_TRUE(acceptVisitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchResultHasCorrectName) {
    createSong("specific_name.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("specific", visitor);
    EXPECT_TRUE(visitor.hasName("specific_name.mp3"));
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchAllSongsMatch) {
    createSong("song_a.mp3");
    createSong("song_b.mp3");
    createSong("song_c.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("song", visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(SearchSongUseCaseTest, SearchNoSongsMatch) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("zzz", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(SearchSongUseCaseTest, SearchAfterSortFindsAll) {
    createSong("rock_a.mp3");
    createSong("rock_b.mp3");
    createSong("jazz.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    model.sort(true);
    TestPlaylistVisitor visitor;
    model.search("rock", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(SearchSongUseCaseTest, SearchLongQuery) {
    createSong("very_long_song_name_here.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("very_long_song_name_here", visitor);
    EXPECT_TRUE(visitor.hasName("very_long_song_name_here.mp3"));
}

TEST_F(SearchSongUseCaseTest, SearchSingleSongPlaylist) {
    createSong("only.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    model.search("only", visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(SearchSongUseCaseTest, SearchDoesNotCrashOnEmptyPlaylist) {
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor visitor;
    EXPECT_NO_THROW(model.search("test", visitor));
}

TEST_F(SearchSongUseCaseTest, SearchVisitorIsIndependent) {
    createSong("a.mp3");
    createSong("b.mp3");
    Model model(musicDir, adsDir);
    model.add(listener);
    TestPlaylistVisitor v1;
    model.search("a", v1);
    TestPlaylistVisitor v2;
    model.search("b", v2);
    EXPECT_TRUE(v1.hasSongs(1));
    EXPECT_TRUE(v2.hasSongs(1));
}
