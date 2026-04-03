#ifndef MUSICLIBRARYTEST_H
#define MUSICLIBRARYTEST_H

#include "../DirectoryTestFixture.h"

class MusicLibraryTest : public DirectoryTestFixture {
protected:
    std::string identify() const override;
};

#endif