#include "FileMetadataTest.h"
#include "model/core/FileMetadata.h"
#include <fstream>

std::string FileMetadataTest::identify() const {
    return "file_metadata_test";
}

TEST_F(FileMetadataTest, StampReturnsZeroForMissingFile) {
    EXPECT_EQ(0, FileMetadata("/nonexistent/path/file.mp3").stamp());
}

TEST_F(FileMetadataTest, StampReturnsNonZeroForExistingFile) {
    createFile("present.mp3");
    EXPECT_GT(FileMetadata(test_directory_ + "/present.mp3").stamp(), 0);
}

TEST_F(FileMetadataTest, LastReturnsZeroForMissingFile) {
    EXPECT_EQ(0, FileMetadata("/nonexistent/path/file.mp3").last());
}

TEST_F(FileMetadataTest, LastReturnsFileSize) {
    const std::string path = test_directory_ + "/sized.mp3";
    std::ofstream(path) << std::string(123, 'x');
    EXPECT_EQ(123, FileMetadata(path).last());
}

TEST_F(FileMetadataTest, LastDistinguishesFileSizes) {
    const std::string small = test_directory_ + "/small.mp3";
    const std::string large = test_directory_ + "/large.mp3";
    std::ofstream(small) << std::string(50, 'x');
    std::ofstream(large) << std::string(500, 'x');
    EXPECT_LT(FileMetadata(small).last(), FileMetadata(large).last());
}
