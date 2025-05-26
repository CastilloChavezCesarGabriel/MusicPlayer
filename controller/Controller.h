#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/Model.h"
#include "../view/View.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <stack>

class Controller final : public QObject {
    Q_OBJECT
private:
    Model *model_;
    View *view_;
    QMediaPlayer *media_player_;
    QAudioOutput *audio_output_;
    std::stack<int> song_stack_;
    std::string base_path;
    std::string current_id_;
    std::string selected_id_;
    bool repeat_ = false;

    void handleSongStatus();
    void handleDrop(const QList<QUrl> &urls);
    void processSelection(int song_id, bool updateSelectedId);

    void handleAdStatus();
    void processRandomAd() const;

    void onPlay(const std::string& filePath) const;
    void updatePlaylist(const std::string &id);
    void handlePlayback(int song_id) const;

    std::string onSaveId() const;
    void onRestoreId(const std::string &song_id);
    static bool isPlayback();
    static std::vector<std::string> toStringVector(const QList<QUrl> &input);

public:
    explicit Controller(Model *model, View *view, QObject *parent = nullptr);

public slots:
    void onPlaySelected();
    void onPlayNext();
    void onPlayPrevious();
    void onRepeat();
    void onAdd();
    void onRemove();
    void onSkipAd();
    void onSortByNumber();
    void onSortByName();
    void onUpdateVolume(int volume) const;
    void onSearch(const QString& text) const;
    void handleMediaStatus(QMediaPlayer::MediaStatus status);
};

#endif //CONTROLLER_H
