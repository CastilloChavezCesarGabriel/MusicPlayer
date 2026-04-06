#ifndef I_SEARCH_PANEL_H
#define I_SEARCH_PANEL_H

#include <string>
#include <vector>

class ISearchPanel {
public:
    virtual ~ISearchPanel() = default;
    virtual void suggest(const std::vector<std::string>& names) = 0;
    virtual void dismiss() = 0;
};

#endif //I_SEARCH_PANEL_H
