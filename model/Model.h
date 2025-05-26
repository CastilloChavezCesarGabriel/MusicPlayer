#ifndef MODEL_H
#define MODEL_H
#include <QObject>
#include <QStringList>
#include "SongSorting.h"

class Model final : public QObject {
    Q_OBJECT
private:
    std::vector<std::string> song_names_;
    std::vector<Song> songs_;
    std::vector<std::string> ads_;
    std::string base_path_;
    std::string resources_path_;
    std::string ads_path_;
    std::string music_path_;
    bool playing_ad_ = false;
    SongSorting sorting;

public:
    explicit Model(QObject *parent = nullptr);

    void shuffle();
    void sortByName();
    void sortByNumber();
    std::vector<std::string> getSongs() const;
    std::string getIndex(int index) const;
    int getId(const std::string &id) const;
    bool isPlayingAd() const;
    std::string getFilePath(int index) const;
    void setPlayingAd(bool state);
    void add(const std::string &file_path);
    void remove(const std::string &file_path);
    void drop(const std::vector<std::string> &urls);
    std::vector<Song> search(const std::string& query) const;
    std::string getRandomAd() const;

signals:
    void songsUpdated(const std::vector<std::string> &songs);
    void adsUpdated(const std::vector<std::string> &ads);
    void disableButtons();
    void userFeedback(const QString &message, bool success);

private:
    void loadMusic();
    void loadAds();
    void updatePlaylist();
    void save(const std::string &file_path) const;
    static bool isExtension(const std::string &file_name);
    std::vector<Song>::iterator find(const std::string &file_path);
    static std::vector<std::string> filter(const std::string &directory);
};

#endif //MODEL_H
