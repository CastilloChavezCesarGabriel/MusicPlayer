#ifndef I_DISPLAY_VIEW_H
#define I_DISPLAY_VIEW_H

#include <string>
#include <vector>

class IDisplayView {
public:
    virtual ~IDisplayView() = default;
    virtual void refresh(const std::vector<std::string>& names) = 0;
    virtual void highlight(int index) = 0;
    virtual void suggest(const std::vector<std::string>& names) = 0;
    virtual void dismiss() = 0;
    virtual void sort(const std::string& label) = 0;
};

#endif //I_DISPLAY_VIEW_H
