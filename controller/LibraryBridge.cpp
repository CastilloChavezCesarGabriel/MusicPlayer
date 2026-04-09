#include "LibraryBridge.h"

LibraryBridge::LibraryBridge(ILibraryView& view) : view_(view) {}

void LibraryBridge::onReveal(const bool visible) { view_.reveal(visible); }
void LibraryBridge::onEnabled(const bool state) { view_.enable(state); }
void LibraryBridge::onSelected(int) { view_.enable(true); }
