#ifndef I_PLAYLIST_PANEL_H
#define I_PLAYLIST_PANEL_H

#include <string>
#include <vector>

class IPlaylistPanel {
public:
    virtual ~IPlaylistPanel() = default;
    virtual void refresh(const std::vector<std::string>& names) = 0;
    virtual void highlight(int index) = 0;
};

#endif //I_PLAYLIST_PANEL_H