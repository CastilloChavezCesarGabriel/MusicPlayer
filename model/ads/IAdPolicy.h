#ifndef I_AD_POLICY_H
#define I_AD_POLICY_H

#include <vector>
#include <string>

class IAdPolicy {
public:
    virtual ~IAdPolicy() = default;
    virtual bool decide() = 0;
    virtual int clock() = 0;
    virtual std::string pick(const std::vector<std::string>& ads) = 0;
};

#endif //I_AD_POLICY_H