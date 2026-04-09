#ifndef ADVERTISEMENTTEST_H
#define ADVERTISEMENTTEST_H

#include "../DirectoryTestFixture.h"
#include "../MockPlaybackListener.h"
#include "model/ads/Dice.h"
#include "model/ads/RandomAdPolicy.h"

class AdvertisementTest : public DirectoryTestFixture {
protected:
    MockPlaybackListener listener_;
    Dice dice_;
    RandomAdPolicy ad_policy_{dice_};

    std::string identify() const override;
};

#endif
