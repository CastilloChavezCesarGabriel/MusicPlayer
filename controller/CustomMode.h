#ifndef CUSTOM_MODE_H
#define CUSTOM_MODE_H

#include "SortMode.h"

class CustomMode final : public SortMode {
public:
    CustomMode();
    void apply(MusicPlayer& musicPlayer) override;
};

#endif //CUSTOM_MODE_H