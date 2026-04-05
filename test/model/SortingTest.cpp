#include "SortingTest.h"
#include <filesystem>
#include <fstream>

void ShellSortTest::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/shell_sort_test";
    std::filesystem::create_directories(test_directory_);
}

void ShellSortTest::TearDown() {
    std::filesystem::remove_all(test_directory_);
}

std::string ShellSortTest::createFile(const std::string& name, const int size) const {
    const std::string path = test_directory_ + "/" + name;
    std::ofstream(path) << std::string(size, 'x');
    return path;
}

TEST_F(ShellSortTest, SortByDurationAscending) {
    const std::string c = createFile("c.mp3", 300);
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    std::vector<Song> songs = {Song("c.mp3", c), Song("a.mp3", a), Song("b.mp3", b)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortAlreadySorted) {
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    const std::string c = createFile("c.mp3", 300);
    std::vector<Song> songs = {Song("a.mp3", a), Song("b.mp3", b), Song("c.mp3", c)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortReversed) {
    const std::string e = createFile("e.mp3", 500);
    const std::string d = createFile("d.mp3", 400);
    const std::string c = createFile("c.mp3", 300);
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {
        Song("e.mp3", e), Song("d.mp3", d), Song("c.mp3", c),
        Song("b.mp3", b), Song("a.mp3", a)
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortSingleElement) {
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {Song("a.mp3", a)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(ShellSortTest, SortDuplicateSizes) {
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    const std::string c = createFile("c.mp3", 200);
    std::vector<Song> songs = {Song("b.mp3", b), Song("a.mp3", a), Song("c.mp3", c)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortPreservesAllElements) {
    const std::string c = createFile("c.mp3", 300);
    const std::string a = createFile("a.mp3", 100);
    const std::string b = createFile("b.mp3", 200);
    std::vector<Song> songs = {Song("c.mp3", c), Song("a.mp3", a), Song("b.mp3", b)};
    sorter_.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(ShellSortTest, SortTwoElements) {
    const std::string b = createFile("b.mp3", 200);
    const std::string a = createFile("a.mp3", 100);
    std::vector<Song> songs = {Song("b.mp3", b), Song("a.mp3", a)};
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "a.mp3"));
}

TEST_F(ShellSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        const std::string name = std::to_string(i) + ".mp3";
        const std::string path = createFile(name, i * 10);
        songs.emplace_back(name, path);
    }
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "1.mp3"));
}

TEST_F(QuickSortTest, SortByNameAlphabetical) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortAlreadySorted) {
    std::vector<Song> songs = {
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b"),
        Song("C.mp3", "/c")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortReversed) {
    std::vector<Song> songs = {
        Song("E.mp3", "/e"),
        Song("D.mp3", "/d"),
        Song("C.mp3", "/c"),
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortSingleElement) {
    std::vector<Song> songs = { Song("A.mp3", "/a") };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortEmptyVector) {
    std::vector<Song> songs;
    sorter_.sort(songs);
    EXPECT_TRUE(songs.empty());
}

TEST_F(QuickSortTest, SortDuplicateNames) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b2")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortLargeCollection) {
    std::vector<Song> songs;
    for (int i = 100; i > 0; i--) {
        songs.emplace_back(std::to_string(i) + ".mp3", "/s");
    }
    sorter_.sort(songs);
    EXPECT_EQ(100, songs.size());
}

TEST_F(QuickSortTest, SortPreservesAllElements) {
    std::vector<Song> songs = {
        Song("C.mp3", "/c"),
        Song("A.mp3", "/a"),
        Song("B.mp3", "/b")
    };
    sorter_.sort(songs);
    EXPECT_EQ(3, songs.size());
}

TEST_F(QuickSortTest, SortTwoElements) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
}

TEST_F(QuickSortTest, SortNumberedSongsByTitle) {
    std::vector<Song> songs = {
        Song("(2) Banana.mp3", "/b"),
        Song("(1) Cherry.mp3", "/c"),
        Song("(3) Apple.mp3", "/a")
    };
    sorter_.sort(songs);
    songs[0].accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "(3) Apple.mp3"));
}
