#ifndef FILE_METADATA_TEST_H
#define FILE_METADATA_TEST_H

#include "../DirectoryTestFixture.h"

class FileMetadataTest : public DirectoryTestFixture {
protected:
    std::string identify() const override;
};

#endif //FILE_METADATA_TEST_H
