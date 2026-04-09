#ifndef DICE_H
#define DICE_H

#include "IDice.h"
#include <random>

class Dice final : public IDice {
private:
    std::mt19937 engine_;

public:
    Dice();
    int roll(int faces) override;
};

#endif //DICE_H