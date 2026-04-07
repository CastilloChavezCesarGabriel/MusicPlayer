#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "../model/Model.h"
#include "../view/IPlayerView.h"
#include <string>

class SearchController {
private:
    Model& model_;
    IPlayerView& view_;

public:
    SearchController(Model& model, IPlayerView& view);
    void search(const std::string& query) const;
};

#endif //SEARCH_CONTROLLER_H