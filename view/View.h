#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QHBoxLayout>
#include <QLabel>

class View final : public QWidget {
    Q_OBJECT
private:
    QPushButton *play_button_{};
    QPushButton *pause_button_{};
    QPushButton *repeat_button_{};
    QPushButton *next_button_{};
    QPushButton *previous_button_{};
    QPushButton *add_button_{};
    QPushButton *remove_button_{};
    QPushButton *skip_button_{};
    QPushButton *sort_by_number_button_;
    QPushButton *sort_by_name_button_;

    QListView *playlist_view_{};
    QStringListModel *playlist_model_{};
    QSlider *volume_slider_{};
    QLabel *volume_label_{};
    QLineEdit* search_bar_{};

    QVBoxLayout *main_layout_{};
    QHBoxLayout *control_layout_{};
    QHBoxLayout *volume_layout_{};
    QHBoxLayout *files_layout_{};
    QHBoxLayout *sort_layout_{};

    void setupUi();
    void setupConnections();

public:
    explicit View(QWidget *parent = nullptr);
    QListView *playlistView() const;
    void enableButtons(bool enable) const;
    void showSkipAd(bool input) const;
    void clearSelection() const;

public slots:
    void updatePlaylist(const std::vector<std::string> &songs) const;
    void updateVolume(int volume) const;
    void updateSelection(int index) const;
    void showUserFeedback(const QString &message, bool success);
    bool showConfirmation(const QString &message);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void onPlayRequested();
    void onPauseRequested();
    void onRepeatRequested();
    void onNextRequested();
    void onPreviousRequested();
    void onAddRequested();
    void onRemoveRequested();
    void onSkipAdRequested();
    void onSortByNumberRequested();
    void onSortByNameRequested();
    void onVolumeChanged(int value);
    void onSearchChanged(const QString& text);
    void filesDropped(const QList<QUrl> &urls);
};

#endif //VIEW_H
