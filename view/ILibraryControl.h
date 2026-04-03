#ifndef I_LIBRARY_CONTROL_H
#define I_LIBRARY_CONTROL_H

#include <string>
#include <vector>

class ILibraryControl {
public:
    virtual ~ILibraryControl() = default;
    virtual void onAdd() = 0;
    virtual void onRemove(int index) = 0;
    virtual void onDrop(const std::vector<std::string>& paths) = 0;
};

#endif //I_LIBRARY_CONTROL_H