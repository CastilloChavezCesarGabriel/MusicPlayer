#include "PlaylistTest.h"

void PlaylistTest::SetUp() {
    testDir = std::filesystem::temp_directory_path().string() + "/playlist_test";
    std::filesystem::create_directories(testDir);
    library = new MusicLibrary(testDir);
    playlist = new Playlist(*library);
}

void PlaylistTest::TearDown() {
    delete playlist;
    delete library;
    std::filesystem::remove_all(testDir);
}

void PlaylistTest::populate(int count) {
    for (int i = 0; i < count; i++) {
        playlist->add(Song("(" + std::to_string(i + 1) + ") Song" + std::to_string(i) + ".mp3",
                          testDir + "/song" + std::to_string(i) + ".mp3"));
    }
}

TEST_F(PlaylistTest, AddSingleSong) {
    playlist->add(Song("A.mp3", "/a"));
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(PlaylistTest, AddMultipleSongs) {
    populate(5);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(5));
}

TEST_F(PlaylistTest, AddPreservesOrder) {
    playlist->add(Song("A.mp3", "/a"));
    playlist->add(Song("B.mp3", "/b"));
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveReducesCount) {
    populate(3);
    playlist->remove(1);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(PlaylistTest, RemoveFirstSong) {
    playlist->add(Song("A.mp3", "/a"));
    playlist->add(Song("B.mp3", "/b"));
    playlist->remove(0);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveLastSong) {
    playlist->add(Song("A.mp3", "/a"));
    playlist->add(Song("B.mp3", "/b"));
    playlist->remove(1);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
    EXPECT_TRUE(visitor.hasName("A.mp3"));
}

TEST_F(PlaylistTest, RemoveInvalidNegativeIndex) {
    populate(3);
    playlist->remove(-1);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveInvalidLargeIndex) {
    populate(3);
    playlist->remove(100);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveFromEmptyPlaylist) {
    playlist->remove(0);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, SortByNameAlphabetical) {
    playlist->add(Song("C.mp3", "/c"));
    playlist->add(Song("A.mp3", "/a"));
    playlist->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist->sort(byName);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "C.mp3"));
}

TEST_F(PlaylistTest, SortByNumberAscending) {
    playlist->add(Song("(3) Third.mp3", "/c"));
    playlist->add(Song("(1) First.mp3", "/a"));
    playlist->add(Song("(2) Second.mp3", "/b"));
    ShellSort byNumber;
    playlist->sort(byNumber);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasNameAt(0, "(1) First.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(1, "(2) Second.mp3"));
    EXPECT_TRUE(visitor.hasNameAt(2, "(3) Third.mp3"));
}

TEST_F(PlaylistTest, SortEmptyPlaylist) {
    QuickSort byName;
    playlist->sort(byName);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, SortSingleSong) {
    playlist->add(Song("A.mp3", "/a"));
    QuickSort byName;
    playlist->sort(byName);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(1));
}

TEST_F(PlaylistTest, ShuffleDoesNotChangeCount) {
    populate(10);
    playlist->shuffle();
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(10));
}

TEST_F(PlaylistTest, ShuffleResetsSelection) {
    populate(5);
    playlist->select(2, listener);
    playlist->shuffle();
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, ClearRemovesAllSongs) {
    populate(5);
    playlist->clear();
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, ClearResetsSelection) {
    populate(5);
    playlist->select(2, listener);
    playlist->clear();
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, SelectValidIndex) {
    populate(3);
    playlist->select(1, listener);
    EXPECT_TRUE(playlist->hasSelected());
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SelectInvalidNegativeIndex) {
    populate(3);
    playlist->select(-1, listener);
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, SelectInvalidLargeIndex) {
    populate(3);
    playlist->select(100, listener);
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, AdvanceMovesToNext) {
    populate(3);
    playlist->select(0, listener);
    playlist->advance(listener);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaylistTest, AdvanceAtEndDoesNothing) {
    populate(3);
    playlist->select(2, listener);
    playlist->advance(listener);
    EXPECT_FALSE(listener.wasSelectedWith(3));
}

TEST_F(PlaylistTest, RetreatMovesToPrevious) {
    populate(3);
    playlist->select(2, listener);
    playlist->retreat(listener);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatAtStartDoesNothing) {
    populate(3);
    playlist->select(0, listener);
    playlist->retreat(listener);
    EXPECT_FALSE(listener.wasSelectedWith(-1));
}

TEST_F(PlaylistTest, PlayCurrentSong) {
    playlist->add(Song("A.mp3", "/a"));
    playlist->select(0, listener);
    playlist->play(visitor);
    EXPECT_TRUE(visitor.hasName("A.mp3"));
}

TEST_F(PlaylistTest, PlayWithNoSelection) {
    populate(3);
    playlist->play(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, SearchFindsMatchingSongs) {
    playlist->add(Song("Hello.mp3", "/a"));
    playlist->add(Song("Goodbye.mp3", "/b"));
    playlist->add(Song("Hello World.mp3", "/c"));
    playlist->search("Hello", visitor);
    EXPECT_TRUE(visitor.hasSongs(2));
}

TEST_F(PlaylistTest, SearchReturnsEmptyForNoMatch) {
    populate(5);
    playlist->search("ZZZZZ", visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, SearchEmptyQueryReturnsAll) {
    populate(3);
    playlist->search("", visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(PlaylistTest, HasNextWhenMoreSongsExist) {
    populate(3);
    playlist->select(0, listener);
    EXPECT_TRUE(playlist->hasNext());
}

TEST_F(PlaylistTest, HasNextFalseAtEnd) {
    populate(3);
    playlist->select(2, listener);
    EXPECT_FALSE(playlist->hasNext());
}

TEST_F(PlaylistTest, HasSelectedFalseInitially) {
    populate(3);
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, HasSelectedTrueAfterSelect) {
    populate(3);
    playlist->select(1, listener);
    EXPECT_TRUE(playlist->hasSelected());
}

TEST_F(PlaylistTest, RemoveCurrentSongResetsSelection) {
    populate(3);
    playlist->select(1, listener);
    playlist->remove(1);
    EXPECT_FALSE(playlist->hasSelected());
}

TEST_F(PlaylistTest, RemoveBeforeCurrentAdjustsIndex) {
    populate(5);
    playlist->select(3, listener);
    playlist->remove(0);
    playlist->play(visitor);
    EXPECT_TRUE(visitor.hasName("(4) Song3.mp3"));
}

TEST_F(PlaylistTest, AcceptEmptyPlaylist) {
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.isEmpty());
}

TEST_F(PlaylistTest, AcceptAllSongs) {
    populate(4);
    playlist->accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(4));
}

TEST_F(PlaylistTest, SelectNotifiesListener) {
    populate(3);
    playlist->select(2, listener);
    EXPECT_TRUE(listener.wasSelected());
}

TEST_F(PlaylistTest, AdvanceNotifiesListener) {
    populate(3);
    playlist->select(0, listener);
    playlist->advance(listener);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatNotifiesListener) {
    populate(3);
    playlist->select(2, listener);
    playlist->retreat(listener);
    EXPECT_TRUE(listener.wasSelectedWith(1));
}
