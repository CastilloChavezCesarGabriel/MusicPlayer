#include "Channel.h"

Channel::Channel(IPlaybackListener& listener)
    : listener_(listener) {
}

void Channel::visit(const std::string&, const std::string& path) {
    listener_.onStart(path);
}