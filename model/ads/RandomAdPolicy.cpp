#include "model/ads/RandomAdPolicy.h"

RandomAdPolicy::RandomAdPolicy(IDice& dice) : dice_(dice) {}

bool RandomAdPolicy::decide() {
    return dice_.roll(100) <= 25;
}

int RandomAdPolicy::clock() {
    return (dice_.roll(6) + 4) * 1000;
}

std::string RandomAdPolicy::pick(const std::vector<std::string>& ads) {
    if (ads.empty()) return "";
    const int index = dice_.roll(static_cast<int>(ads.size())) - 1;
    return ads.at(index);
}