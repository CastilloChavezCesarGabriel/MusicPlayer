#ifndef CHANNEL_H
#define CHANNEL_H

#include "IPlaylistVisitor.h"
#include "IPlaybackListener.h"

class Channel final : public IPlaylistVisitor {
private:
    IPlaybackListener& listener_;

public:
    explicit Channel(IPlaybackListener& listener);
    void visit(const std::string& name, const std::string& path) override;
};

#endif //CHANNEL_H