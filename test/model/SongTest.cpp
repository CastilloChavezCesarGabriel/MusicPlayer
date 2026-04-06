#include "SongTest.h"
#include "../../model/Song.h"
#include <filesystem>
#include <fstream>

TEST_F(SongTest, AcceptPassesNameToVisitor) {
    Song song("(1) First Song.mp3", "/music/(1) First Song.mp3");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasName("(1) First Song.mp3"));
}

TEST_F(SongTest, AcceptPassesPathToVisitor) {
    Song song("song.mp3", "/music/song.mp3");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasPath("/music/song.mp3"));
}

TEST_F(SongTest, MatchFindsSubstring) {
    Song song("Beautiful Now.mp3", "/music/Beautiful Now.mp3");
    EXPECT_TRUE(song.matches("Beautiful"));
}

TEST_F(SongTest, MatchFindsExactName) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_TRUE(song.matches("Hello.wav"));
}

TEST_F(SongTest, MatchReturnsFalseForMismatch) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("Goodbye"));
}

TEST_F(SongTest, MatchIsCaseSensitive) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.matches("hello"));
}

TEST_F(SongTest, MatchFindsPartialName) {
    Song song("Counting Stars.mp3", "/music/Counting Stars.mp3");
    EXPECT_TRUE(song.matches("Stars"));
}

TEST_F(SongTest, MatchEmptyQueryMatchesAll) {
    Song song("anything.mp3", "/music/anything.mp3");
    EXPECT_TRUE(song.matches(""));
}

TEST_F(SongTest, ParseExtractsNameFromNumberedFormat) {
    EXPECT_EQ("First Song.mp3", Song::parse("(1) First Song.mp3"));
}

TEST_F(SongTest, ParseReturnsOriginalWhenNoNumber) {
    EXPECT_EQ("Hello.wav", Song::parse("Hello.wav"));
}

TEST_F(SongTest, ParseTrimsWhitespace) {
    EXPECT_EQ("Song.mp3", Song::parse("  Song.mp3  "));
}

TEST_F(SongTest, ParseHandlesMultiDigitNumbers) {
    EXPECT_EQ("Tenth Song.mp3", Song::parse("(10) Tenth Song.mp3"));
}

TEST_F(SongTest, ParseReturnsEmptyForWhitespaceOnly) {
    EXPECT_EQ("", Song::parse("   "));
}

TEST_F(SongTest, AcceptMultipleSongsToSameVisitor) {
    Song first("A.mp3", "/a");
    Song second("B.mp3", "/b");
    first.accept(visitor_);
    second.accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(SongTest, AcceptPreservesOrderInVisitor) {
    Song first("A.mp3", "/a");
    Song second("B.mp3", "/b");
    first.accept(visitor_);
    second.accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(SongTest, MatchWithSpecialCharacters) {
    Song song("I'm good (Blue).mp3", "/music/I'm good (Blue).mp3");
    EXPECT_TRUE(song.matches("(Blue)"));
}

TEST_F(SongTest, ConstructionWithEmptyName) {
    Song song("", "/music/empty");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasName(""));
}

TEST_F(SongTest, ConstructionWithEmptyPath) {
    Song song("song.mp3", "");
    song.accept(visitor_);
    EXPECT_TRUE(visitor_.hasPath(""));
}

TEST_F(SongTest, ParseHandlesEmptyString) {
    EXPECT_EQ("", Song::parse(""));
}

TEST_F(SongTest, StampReturnsZeroForMissingFile) {
    EXPECT_EQ(0, Song::stamp("/nonexistent/path/file.mp3"));
}

TEST_F(SongTest, StampReturnsNonZeroForExistingFile) {
    const std::string path = std::filesystem::temp_directory_path().string() + "/song_stamp_test.mp3";
    std::ofstream(path) << "audio";
    EXPECT_GT(Song::stamp(path), 0);
    std::filesystem::remove(path);
}

TEST_F(SongTest, LastReturnsZeroForMissingFile) {
    EXPECT_EQ(0, Song::last("/nonexistent/path/file.mp3"));
}

TEST_F(SongTest, LastReturnsFileSize) {
    const std::string path = std::filesystem::temp_directory_path().string() + "/song_last_test.mp3";
    std::ofstream(path) << std::string(123, 'x');
    EXPECT_EQ(123, Song::last(path));
    std::filesystem::remove(path);
}

TEST_F(SongTest, LastDistinguishesFileSizes) {
    const std::string small = std::filesystem::temp_directory_path().string() + "/song_small.mp3";
    const std::string large = std::filesystem::temp_directory_path().string() + "/song_large.mp3";
    std::ofstream(small) << std::string(50, 'x');
    std::ofstream(large) << std::string(500, 'x');
    EXPECT_LT(Song::last(small), Song::last(large));
    std::filesystem::remove(small);
    std::filesystem::remove(large);
}