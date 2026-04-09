#include "PlaylistTest.h"
#include "model/arrangement/DurationSort.h"
#include "model/arrangement/QuickSort.h"
#include "model/events/IPlaybackListener.h"
#include <filesystem>
#include <fstream>

void PlaylistTest::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/playlist_test";
    std::filesystem::create_directories(test_directory_);
    library_ = new MusicLibrary(test_directory_);
    playlist_ = new Playlist(*library_);
}

void PlaylistTest::TearDown() {
    delete playlist_;
    delete library_;
    std::filesystem::remove_all(test_directory_);
}

void PlaylistTest::populate(int count) const {
    for (int i = 0; i < count; i++) {
        playlist_->add(Song("(" + std::to_string(i + 1) + ") Song" + std::to_string(i) + ".mp3",
                          test_directory_ + "/song" + std::to_string(i) + ".mp3"));
    }
}

TEST_F(PlaylistTest, AddSingleSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, AddMultipleSongs) {
    populate(5);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(5));
}

TEST_F(PlaylistTest, AddPreservesOrder) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveReducesCount) {
    populate(3);
    playlist_->remove(1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, RemoveFirstSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->remove(0);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "B.mp3"));
}

TEST_F(PlaylistTest, RemoveLastSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->remove(1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
    EXPECT_TRUE(visitor_.hasName("A.mp3"));
}

TEST_F(PlaylistTest, RemoveInvalidNegativeIndex) {
    populate(3);
    playlist_->remove(-1);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveInvalidLargeIndex) {
    populate(3);
    playlist_->remove(100);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, RemoveFromEmptyPlaylist) {
    playlist_->remove(0);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortByNameAlphabetical) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "C.mp3"));
}

TEST_F(PlaylistTest, SortByDurationAscending) {
    const std::string large = test_directory_ + "/large.mp3";
    const std::string small = test_directory_ + "/small.mp3";
    const std::string medium = test_directory_ + "/medium.mp3";
    std::ofstream(large) << std::string(300, 'x');
    std::ofstream(small) << std::string(100, 'x');
    std::ofstream(medium) << std::string(200, 'x');
    playlist_->add(Song("large.mp3", large));
    playlist_->add(Song("small.mp3", small));
    playlist_->add(Song("medium.mp3", medium));
    DurationSort byDuration;
    playlist_->sort(byDuration);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "small.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "medium.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "large.mp3"));
}

TEST_F(PlaylistTest, SortEmptyPlaylist) {
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SortSingleSong) {
    playlist_->add(Song("A.mp3", "/a"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(1));
}

TEST_F(PlaylistTest, ShuffleDoesNotChangeCount) {
    populate(10);
    playlist_->shuffle();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(10));
}

TEST_F(PlaylistTest, ShufflePreservesSelection) {
    populate(5);
    playlist_->select(2, listener_);
    playlist_->shuffle();
    EXPECT_TRUE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, ClearRemovesAllSongs) {
    populate(5);
    playlist_->clear();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ClearResetsSelection) {
    populate(5);
    playlist_->select(2, listener_);
    playlist_->clear();
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, SelectValidIndex) {
    populate(3);
    playlist_->select(1, listener_);
    EXPECT_TRUE(playlist_->hasSelected());
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SelectInvalidNegativeIndex) {
    populate(3);
    playlist_->select(-1, listener_);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, SelectInvalidLargeIndex) {
    populate(3);
    playlist_->select(100, listener_);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, AdvanceMovesToNext) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, AdvanceAtEndDoesNothing) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->advance(listener_);
    EXPECT_FALSE(listener_.wasSelectedWith(3));
}

TEST_F(PlaylistTest, RetreatMovesToPrevious) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatAtStartDoesNothing) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->retreat(listener_);
    EXPECT_FALSE(listener_.wasSelectedWith(-1));
}

TEST_F(PlaylistTest, PlayCurrentSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->select(0, listener_);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.hasName("A.mp3"));
}

TEST_F(PlaylistTest, PlayWithNoSelection) {
    populate(3);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SearchFindsMatchingSongs) {
    playlist_->add(Song("Hello.mp3", "/a"));
    playlist_->add(Song("Goodbye.mp3", "/b"));
    playlist_->add(Song("Hello World.mp3", "/c"));
    playlist_->search("Hello", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(2));
}

TEST_F(PlaylistTest, SearchReturnsEmptyForNoMatch) {
    populate(5);
    playlist_->search("ZZZZZ", visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, SearchEmptyQueryReturnsAll) {
    populate(3);
    playlist_->search("", visitor_);
    EXPECT_TRUE(visitor_.hasSongs(3));
}

TEST_F(PlaylistTest, HasNextWhenMoreSongsExist) {
    populate(3);
    playlist_->select(0, listener_);
    EXPECT_TRUE(playlist_->hasNext());
}

TEST_F(PlaylistTest, HasNextFalseAtEnd) {
    populate(3);
    playlist_->select(2, listener_);
    EXPECT_FALSE(playlist_->hasNext());
}

TEST_F(PlaylistTest, HasSelectedFalseInitially) {
    populate(3);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, HasSelectedTrueAfterSelect) {
    populate(3);
    playlist_->select(1, listener_);
    EXPECT_TRUE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, RemoveCurrentSongResetsSelection) {
    populate(3);
    playlist_->select(1, listener_);
    playlist_->remove(1);
    EXPECT_FALSE(playlist_->hasSelected());
}

TEST_F(PlaylistTest, RemoveBeforeCurrentAdjustsIndex) {
    populate(5);
    playlist_->select(3, listener_);
    playlist_->remove(0);
    playlist_->play(visitor_);
    EXPECT_TRUE(visitor_.hasName("(4) Song3.mp3"));
}

TEST_F(PlaylistTest, AcceptEmptyPlaylist) {
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, AcceptAllSongs) {
    populate(4);
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasSongs(4));
}

TEST_F(PlaylistTest, SelectNotifiesListener) {
    populate(3);
    playlist_->select(2, listener_);
    EXPECT_TRUE(listener_.wasSelected());
}

TEST_F(PlaylistTest, AdvanceNotifiesListener) {
    populate(3);
    playlist_->select(0, listener_);
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RetreatNotifiesListener) {
    populate(3);
    playlist_->select(2, listener_);
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, ReverseInvertsOrder) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->reverse();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "A.mp3"));
}

TEST_F(PlaylistTest, ReverseEmptyPlaylist) {
    playlist_->reverse();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.isEmpty());
}

TEST_F(PlaylistTest, ReversePreservesCurrentSong) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->select(0, listener_);
    playlist_->reverse();
    playlist_->retreat(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, RestoreReturnsOriginalOrder) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}

TEST_F(PlaylistTest, RestoreDoesNothingWhenNothingPreserved) {
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "B.mp3"));
}

TEST_F(PlaylistTest, RestorePreservesCurrentSong) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    playlist_->select(0, listener_);
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->restore();
    playlist_->advance(listener_);
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(PlaylistTest, SortReverseRestoreFullCycle) {
    playlist_->add(Song("C.mp3", "/c"));
    playlist_->add(Song("A.mp3", "/a"));
    playlist_->add(Song("B.mp3", "/b"));
    QuickSort byName;
    playlist_->sort(byName);
    playlist_->reverse();
    playlist_->restore();
    playlist_->accept(visitor_);
    EXPECT_TRUE(visitor_.hasNameAt(0, "C.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(1, "A.mp3"));
    EXPECT_TRUE(visitor_.hasNameAt(2, "B.mp3"));
}