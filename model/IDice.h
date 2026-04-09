#ifndef I_DICE_H
#define I_DICE_H

class IDice {
public:
    virtual ~IDice() = default;
    virtual int roll(int faces) = 0;
};

#endif //I_DICE_H