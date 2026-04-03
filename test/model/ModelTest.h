#ifndef MODELTEST_H
#define MODELTEST_H

#include "../ModelTestFixture.h"
#include "../../model/Model.h"

class ModelTest : public ModelTestFixture {
protected:
    std::string identify() const override;
    Model create() const;
};

#endif