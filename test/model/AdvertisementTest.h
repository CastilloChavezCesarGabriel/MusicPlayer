#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"
#include "../../model/Dice.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;
    Dice dice_;

    std::string identify() const override;
};

#endif
