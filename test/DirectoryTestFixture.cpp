#include "DirectoryTestFixture.h"
#include <filesystem>
#include <fstream>

void DirectoryTestFixture::SetUp() {
    test_directory_ = std::filesystem::temp_directory_path().string() + "/" + identify();
    std::filesystem::create_directories(test_directory_);
}

void DirectoryTestFixture::TearDown() {
    std::filesystem::remove_all(test_directory_);
}

void DirectoryTestFixture::createFile(const std::string& name) const {
    std::ofstream(test_directory_ + "/" + name).close();
}