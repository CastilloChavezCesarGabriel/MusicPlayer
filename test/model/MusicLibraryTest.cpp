#include "MusicLibraryTest.h"
#include "../../model/MusicLibrary.h"
#include "../TestPlaylistVisitor.h"
#include <fstream>

std::string MusicLibraryTest::identify() const {
    return "library_test";
}

TEST_F(MusicLibraryTest, ScanFindsMp3Files) {
    createFile("song.mp3");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(1, result.size());
}

TEST_F(MusicLibraryTest, ScanFindsWavFiles) {
    createFile("song.wav");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(1, result.size());
}

TEST_F(MusicLibraryTest, ScanIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanMixedFiles) {
    createFile("song.mp3");
    createFile("readme.txt");
    createFile("audio.wav");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(2, result.size());
}

TEST_F(MusicLibraryTest, ScanEmptyDirectory) {
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanNonExistentDirectory) {
    auto result = MusicLibrary::scan("/nonexistent");
    EXPECT_EQ(0, result.size());
}

TEST_F(MusicLibraryTest, ScanMultipleMp3) {
    for (int i = 0; i < 10; i++) {
        createFile("song" + std::to_string(i) + ".mp3");
    }
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_EQ(10, result.size());
}

TEST_F(MusicLibraryTest, IsSupportedMp3) {
    EXPECT_TRUE(MusicLibrary::isSupported("song.mp3"));
}

TEST_F(MusicLibraryTest, IsSupportedWav) {
    EXPECT_TRUE(MusicLibrary::isSupported("song.wav"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsTxt) {
    EXPECT_FALSE(MusicLibrary::isSupported("readme.txt"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsPng) {
    EXPECT_FALSE(MusicLibrary::isSupported("image.png"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsNoExtension) {
    EXPECT_FALSE(MusicLibrary::isSupported("noextension"));
}

TEST_F(MusicLibraryTest, IsSupportedRejectsFlac) {
    EXPECT_FALSE(MusicLibrary::isSupported("song.flac"));
}

TEST_F(MusicLibraryTest, IsSupportedWithPath) {
    EXPECT_TRUE(MusicLibrary::isSupported("/music/dir/song.mp3"));
}

TEST_F(MusicLibraryTest, IsSupportedEmptyString) {
    EXPECT_FALSE(MusicLibrary::isSupported(""));
}

TEST_F(MusicLibraryTest, LoadCreatesSongObjects) {
    createFile("song1.mp3");
    createFile("song2.wav");
    MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    EXPECT_EQ(2, songs.size());
}

TEST_F(MusicLibraryTest, LoadEmptyDirectory) {
    MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    EXPECT_EQ(0, songs.size());
}

TEST_F(MusicLibraryTest, LoadNonExistentDirectory) {
    MusicLibrary lib("/nonexistent");
    auto songs = lib.load();
    EXPECT_EQ(0, songs.size());
}

TEST_F(MusicLibraryTest, ContainsExistingFile) {
    createFile("exists.mp3");
    MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("exists.mp3"));
}

TEST_F(MusicLibraryTest, ContainsMissingFile) {
    MusicLibrary lib(test_directory_);
    EXPECT_FALSE(lib.contains("missing.mp3"));
}

TEST_F(MusicLibraryTest, ImportCopiesFile) {
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "data";

    MusicLibrary lib(test_directory_);
    lib.import(srcDir + "/new.mp3");
    EXPECT_TRUE(lib.contains("new.mp3"));
}

TEST_F(MusicLibraryTest, ImportReturnsSong) {
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/new.mp3") << "data";

    const MusicLibrary lib(test_directory_);
    const Song song = lib.import(srcDir + "/new.mp3");
    TestPlaylistVisitor visitor;
    song.accept(visitor);
    EXPECT_TRUE(visitor.hasName("new.mp3"));
}

TEST_F(MusicLibraryTest, ImportDoesNotDuplicateExisting) {
    createFile("existing.mp3");
    const std::string srcDir = test_directory_ + "/src";
    std::filesystem::create_directories(srcDir);
    std::ofstream(srcDir + "/existing.mp3") << "different data";

    const MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("existing.mp3"));
}

TEST_F(MusicLibraryTest, VisitErasesFile) {
    createFile("to_delete.mp3");
    MusicLibrary lib(test_directory_);
    EXPECT_TRUE(lib.contains("to_delete.mp3"));
    lib.visit("to_delete.mp3", test_directory_ + "/to_delete.mp3");
    EXPECT_FALSE(lib.contains("to_delete.mp3"));
}

TEST_F(MusicLibraryTest, ScanReturnsFullPaths) {
    createFile("song.mp3");
    auto result = MusicLibrary::scan(test_directory_);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result[0].find(test_directory_) != std::string::npos);
}

TEST_F(MusicLibraryTest, LoadSongsAcceptVisitor) {
    createFile("test.mp3");
    const MusicLibrary lib(test_directory_);
    auto songs = lib.load();
    TestPlaylistVisitor visitor;
    songs[0].accept(visitor);
    EXPECT_TRUE(visitor.hasName("test.mp3"));
}