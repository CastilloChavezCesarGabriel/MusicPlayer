#ifndef DIRECTORY_TEST_FIXTURE_H
#define DIRECTORY_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include <string>

class DirectoryTestFixture : public ::testing::Test {
protected:
    std::string test_directory_;

    void SetUp() override;
    void TearDown() override;
    void createFile(const std::string& name) const;

    virtual std::string identify() const = 0;
};

#endif //DIRECTORY_TEST_FIXTURE_H