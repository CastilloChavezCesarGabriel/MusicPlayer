#ifndef REGRESSIONTEST_H
#define REGRESSIONTEST_H

#include "ModelTestFixture.h"

class RegressionTest : public ModelTestFixture {
protected:
    std::string identify() const override;
};

#endif