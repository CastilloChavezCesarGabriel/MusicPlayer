#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/Model.h"
#include "../model/IPlaybackListener.h"
#include "../view/IPlayerView.h"
#include "../view/IPlayerListener.h"

class Controller final : public IPlaybackListener, public IPlayerListener {
private:
    Model& model_;
    IPlayerView& view_;

    void refresh(const std::string& query = "") const;

public:
    Controller(Model& model, IPlayerView& view);

    void onStart(const std::string& path) override;
    void onChanged() override;
    void onSelected(int index) override;
    void onEnabled(bool state) override;
    void onReveal(bool visible) override;
    void onFeedback(const std::string& message, bool success) override;
    void onPlay(int index) override;
    void onResume() override;
    void onPause() override;
    void onRepeat() override;
    void onAdvance() override;
    void onRetreat() override;
    void onAdd() override;
    void onRemove(int index) override;
    void onSkip() override;
    void onSort(bool byName) override;
    void onSearch(const std::string& query) override;
    void onDrop(const std::vector<std::string>& paths) override;
    void onAdjust(int volume) override;
    void onEnd() override;
};

#endif //CONTROLLER_H