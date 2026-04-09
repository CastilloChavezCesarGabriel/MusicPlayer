#ifndef I_LIBRARY_BOARD_H
#define I_LIBRARY_BOARD_H

#include "ILibraryControl.h"

class ILibraryBoard {
public:
    virtual ~ILibraryBoard() = default;
    virtual void bind(ILibraryControl& listener) = 0;
};

#endif //I_LIBRARY_BOARD_H