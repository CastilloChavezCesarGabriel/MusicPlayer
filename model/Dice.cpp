#include "Dice.h"

Dice::Dice() : engine_(std::random_device{}()) {}

int Dice::roll(const int faces) {
    if (faces <= 0) return 0;
    std::uniform_int_distribution<> distribution(1, faces);
    return distribution(engine_);
}