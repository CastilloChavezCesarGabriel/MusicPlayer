#include "CustomMode.h"

CustomMode::CustomMode() : SortMode("Custom", nullptr) {}

void CustomMode::apply(Model& model) {
    model.restore();
}