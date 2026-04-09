#include "RegressionTest.h"
#include "../model/Song.h"
#include "../model/Playlist.h"
#include "../model/MusicLibrary.h"
#include "../model/MusicPlayer.h"
#include "../model/Dice.h"
#include "../model/DurationSort.h"
#include "../model/QuickSort.h"
#include "TestPlaylistVisitor.h"
#include <filesystem>
#include <fstream>

std::string RegressionTest::identify() const {
    return "regression_test";
}

TEST_F(RegressionTest, SortEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, SortSingleSongDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}

TEST_F(RegressionTest, ShellSortEmptyDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
}

TEST_F(RegressionTest, ModelRefreshDoesNotRecurse) {
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
    EXPECT_TRUE(listener_.wasChanged());
}

TEST_F(RegressionTest, ModelSortByNameDoesNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    EXPECT_NO_THROW(musicPlayer.sort(byTitle));
}

TEST_F(RegressionTest, ModelSortByNumberDoesNotCrash) {
    createSong("(3) C.mp3");
    createSong("(1) A.mp3");
    createSong("(2) B.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    DurationSort byDuration;
    EXPECT_NO_THROW(musicPlayer.sort(byDuration));
}

TEST_F(RegressionTest, AdvanceUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.play(0);
    musicPlayer.advance();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RetreatUpdatesSelection) {
    createSong("a.mp3");
    createSong("b.mp3");
    createSong("c.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.play(2);
    musicPlayer.retreat();
    EXPECT_TRUE(listener_.wasSelectedWith(1));
}

TEST_F(RegressionTest, RemoveBeforeCurrentAdjustsSelection) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    MockPlaybackListener listener_;
    playlist.add(Song("A.mp3", "/a"));
    playlist.add(Song("B.mp3", "/b"));
    playlist.add(Song("C.mp3", "/c"));
    playlist.select(2, listener_);
    playlist.remove(0);
    EXPECT_TRUE(playlist.hasSelected());
}

TEST_F(RegressionTest, QuickSortPartitionDoesNotUnderflow) {
    std::vector<Song> songs = {
        Song("B.mp3", "/b"),
        Song("A.mp3", "/a")
    };
    QuickSort sorter;
    EXPECT_NO_THROW(sorter.sort(songs));
}

TEST_F(RegressionTest, InsertUnsupportedFileGivesFeedback) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.insert("");
    EXPECT_TRUE(listener_.wasFeedback("Unsupported file type."));
}

TEST_F(RegressionTest, InsertDuplicateGivesFeedback) {
    createSong("dup.mp3");
    std::string srcDir = base_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/dup.mp3") << "data";

    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.insert(srcDir + "/dup.mp3");
    EXPECT_TRUE(listener_.wasFeedback("This song already exists."));
}

TEST_F(RegressionTest, SortPreservesAllSongs) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    TestPlaylistVisitor visitor;
    musicPlayer.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(3));
}

TEST_F(RegressionTest, ShufflePreservesAllSongs) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    for (int i = 0; i < 20; i++) {
        playlist.add(Song(std::to_string(i) + ".mp3", "/s"));
    }
    playlist.shuffle();
    TestPlaylistVisitor visitor;
    playlist.accept(visitor);
    EXPECT_TRUE(visitor.hasSongs(20));
}

TEST_F(RegressionTest, RepeatCycles) {
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    musicPlayer.repeat();
    musicPlayer.repeat();
    musicPlayer.repeat();
    EXPECT_NO_THROW(musicPlayer.repeat());
}

TEST_F(RegressionTest, RemoveFromEmptyPlaylistDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    EXPECT_NO_THROW(playlist.remove(0));
}

TEST_F(RegressionTest, RemoveNegativeIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    EXPECT_NO_THROW(playlist.remove(-1));
}

TEST_F(RegressionTest, SelectInvalidIndexDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    MockPlaybackListener listener_;
    EXPECT_NO_THROW(playlist.select(999, listener_));
}

TEST_F(RegressionTest, PlayWithNoSelectionDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    playlist.add(Song("A.mp3", "/a"));
    TestPlaylistVisitor visitor;
    EXPECT_NO_THROW(playlist.play(visitor));
}

TEST_F(RegressionTest, ConcludeWithoutInterruptReturnsFalse) {
    Dice dice;
    Advertisement ad(ads_directory_, dice);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(RegressionTest, MultipleSortsDoNotCrash) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            QuickSort byTitle;
            EXPECT_NO_THROW(musicPlayer.sort(byTitle));
        } else {
            DurationSort byDuration;
            EXPECT_NO_THROW(musicPlayer.sort(byDuration));
        }
    }
}

TEST_F(RegressionTest, SortThenAdvanceWorks) {
    createSong("c.mp3");
    createSong("a.mp3");
    createSong("b.mp3");
    MusicPlayer musicPlayer(base_directory_, dice_);
    MockPlaybackListener listener_;
    musicPlayer.subscribe(listener_);
    QuickSort byTitle;
    musicPlayer.sort(byTitle);
    musicPlayer.play(0);
    EXPECT_NO_THROW(musicPlayer.advance());
}

TEST_F(RegressionTest, LargePlaylistSortDoesNotCrash) {
    MusicLibrary lib(music_directory_);
    Playlist playlist(lib);
    for (int i = 500; i > 0; i--) {
        playlist.add(Song("(" + std::to_string(i) + ") Song.mp3", "/s"));
    }
    DurationSort byNumber;
    EXPECT_NO_THROW(playlist.sort(byNumber));
    QuickSort byName;
    EXPECT_NO_THROW(playlist.sort(byName));
}