#include "CustomMode.h"

CustomMode::CustomMode() : SortMode("Custom") {}

void CustomMode::apply(Model& model) {
    model.restore();
}
