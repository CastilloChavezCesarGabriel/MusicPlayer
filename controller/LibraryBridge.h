#ifndef LIBRARY_BRIDGE_H
#define LIBRARY_BRIDGE_H

#include "model/events/ILibraryEvent.h"
#include "../view/ILibraryView.h"

class LibraryBridge final : public ILibraryEvent {
private:
    ILibraryView& view_;

public:
    explicit LibraryBridge(ILibraryView& view);

    void onReveal(bool visible) override;
    void onEnabled(bool state) override;
    void onSelected(int index) override;
};

#endif //LIBRARY_BRIDGE_H
