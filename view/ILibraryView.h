#ifndef I_LIBRARY_VIEW_H
#define I_LIBRARY_VIEW_H

#include <string>

class ILibraryView {
public:
    virtual ~ILibraryView() = default;
    virtual std::string browse() = 0;
    virtual bool confirm(const std::string& message) = 0;
    virtual void reveal(bool visible) = 0;
    virtual void enable(bool state) = 0;
};

#endif //I_LIBRARY_VIEW_H