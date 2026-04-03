#include "SongTest.h"
#include "../../model/Song.h"

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
    EXPECT_TRUE(song.match("Beautiful"));
}

TEST_F(SongTest, MatchFindsExactName) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_TRUE(song.match("Hello.wav"));
}

TEST_F(SongTest, MatchReturnsFalseForMismatch) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.match("Goodbye"));
}

TEST_F(SongTest, MatchIsCaseSensitive) {
    Song song("Hello.wav", "/music/Hello.wav");
    EXPECT_FALSE(song.match("hello"));
}

TEST_F(SongTest, MatchFindsPartialName) {
    Song song("Counting Stars.mp3", "/music/Counting Stars.mp3");
    EXPECT_TRUE(song.match("Stars"));
}

TEST_F(SongTest, MatchEmptyQueryMatchesAll) {
    Song song("anything.mp3", "/music/anything.mp3");
    EXPECT_TRUE(song.match(""));
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

TEST_F(SongTest, OrderExtractsNumberFromParentheses) {
    EXPECT_EQ(3, Song::order("(3) Third Song.mp3"));
}

TEST_F(SongTest, OrderExtractsNumberFromBrackets) {
    EXPECT_EQ(5, Song::order("[5] Fifth Song.mp3"));
}

TEST_F(SongTest, OrderReturnsZeroWhenNoNumber) {
    EXPECT_EQ(0, Song::order("Hello.wav"));
}

TEST_F(SongTest, OrderExtractsSingleDigit) {
    EXPECT_EQ(1, Song::order("(1) First.mp3"));
}

TEST_F(SongTest, OrderExtractsMultiDigit) {
    EXPECT_EQ(42, Song::order("(42) Song.mp3"));
}

TEST_F(SongTest, OrderHandlesLeadingSpaces) {
    EXPECT_EQ(7, Song::order("  (7) Song.mp3"));
}

TEST_F(SongTest, OrderHandlesNumberWithoutParens) {
    EXPECT_EQ(3, Song::order("3 Song.mp3"));
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
    EXPECT_TRUE(song.match("(Blue)"));
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

TEST_F(SongTest, OrderReturnsZeroForEmptyString) {
    EXPECT_EQ(0, Song::order(""));
}

TEST_F(SongTest, ParseHandlesEmptyString) {
    EXPECT_EQ("", Song::parse(""));
}