#include "SortingTest.h"

void ShellSortTest::assertOrder(std::vector<Song>& songs, const std::vector<std::string>& expected) {
    for (int i = 0; i < expected.size(); i++) {
        songs[i].accept(visitor);
    }
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_TRUE(visitor.hasNameAt(i, expected[i]));
    }
}

TEST_F(ShellSortTest, SortByNumberAscending) {
    std::vector<Song> songs = {
        Song("(3) C.mp3", "/c"),
        Song("(1) A.mp3", "/a"),
        Song("(2) B.mp3", "/b")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(ShellSortTest, SortAlreadySorted) {
    std::vector<Song> songs = {
        Song("(1) A.mp3", "/a"),
        Song("(2) B.mp3", "/b"),
        Song("(3) C.mp3", "/c")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(ShellSortTest, SortReversed) {
    std::vector<Song> songs = {
        Song("(5) E.mp3", "/e"),
        Song("(4) D.mp3", "/d"),
        Song("(3) C.mp3", "/c"),
        Song("(2) B.mp3", "/b"),
        Song("(1) A.mp3", "/a")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(ShellSortTest, SortSingleElement) {
    std::vector<Song> songs = { Song("(1) A.mp3", "/a") };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(ShellSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(ShellSortTest, SortDuplicateNumbers) {
    std::vector<Song> songs = {
        Song("(2) B.mp3", "/b"),
        Song("(1) A.mp3", "/a"),
        Song("(2) C.mp3", "/c")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(ShellSortTest, SortSongsWithoutNumbers) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter.sort(songs);
    EXPECT_EQ(2, songs.size());
}

TEST_F(ShellSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        songs.emplace_back("(" + std::to_string(i) + ") Song.mp3", "/s");
    }
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) Song.mp3"));
}

TEST_F(ShellSortTest, SortPreservesAllElements) {
    std::vector<Song> songs = {
        Song("(3) C.mp3", "/c"),
        Song("(1) A.mp3", "/a"),
        Song("(2) B.mp3", "/b")
    };
    sorter.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(ShellSortTest, SortTwoElements) {
    std::vector<Song> songs = {
        Song("(2) B.mp3", "/b"),
        Song("(1) A.mp3", "/a")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) A.mp3"));
}

TEST_F(QuickSortTest, SortByNameAlphabetical) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortAlreadySorted) {
    std::vector<Song> songs = {
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b"),
        Song("C.mp3", "/c")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortReversed) {
    std::vector<Song> songs = {
        Song("E.mp3", "/e"),
        Song("D.mp3", "/d"),
        Song("C.mp3", "/c"),
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortSingleElement) {
    std::vector<Song> songs = { Song("A.mp3", "/a") };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(QuickSortTest, SortDuplicateNames) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b2")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        songs.emplace_back(std::to_string(i) + ".mp3", "/s");
    }
    sorter.sort(songs);
    EXPECT_EQ(100, songs.size());
}

TEST_F(QuickSortTest, SortPreservesAllElements) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(QuickSortTest, SortTwoElements) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortNumberedSongsByTitle) {
    std::vector<Song> songs = {
        Song("(2) Banana.mp3", "/b"),
        Song("(1) Cherry.mp3", "/c"),
        Song("(3) Apple.mp3", "/a")
    };
    sorter.sort(songs);
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(3) Apple.mp3"));
}
