#include "CustomMode.h"

CustomMode::CustomMode() : SortMode("Custom", nullptr) {}

void CustomMode::apply(MusicPlayer& musicPlayer) {
    musicPlayer.restore();
}