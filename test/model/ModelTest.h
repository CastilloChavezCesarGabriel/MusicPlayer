#ifndef MODELTEST_H
#define MODELTEST_H

#include "../ModelTestFixture.h"
#include "model/MusicPlayer.h"

class ModelTest : public ModelTestFixture {
protected:
    std::string identify() const override;
    MusicPlayer create();
};

#endif