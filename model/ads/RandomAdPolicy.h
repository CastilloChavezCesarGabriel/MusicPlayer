#ifndef RANDOM_AD_POLICY_H
#define RANDOM_AD_POLICY_H

#include "model/ads/IAdPolicy.h"
#include "model/ads/IDice.h"

class RandomAdPolicy final : public IAdPolicy {
private:
    IDice& dice_;

public:
    explicit RandomAdPolicy(IDice& dice);
    bool decide() override;
    int clock() override;
    std::string pick(const std::vector<std::string>& ads) override;
};

#endif //RANDOM_AD_POLICY_H