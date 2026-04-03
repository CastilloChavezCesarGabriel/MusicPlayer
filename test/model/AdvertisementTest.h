#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;

    std::string identify() const override;
};

#endif