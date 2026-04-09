#ifndef I_DISPLAY_BOARD_H
#define I_DISPLAY_BOARD_H

#include "IDisplayControl.h"

class IDisplayBoard {
public:
    virtual ~IDisplayBoard() = default;
    virtual void wire(IDisplayControl& listener) = 0;
};

#endif //I_DISPLAY_BOARD_H
