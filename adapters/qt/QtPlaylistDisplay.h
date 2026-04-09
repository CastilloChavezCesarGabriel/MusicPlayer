#ifndef QT_PLAYLIST_DISPLAY_H
#define QT_PLAYLIST_DISPLAY_H

#include <QListView>
#include <QStringListModel>
#include <string>
#include <vector>

class QtPlaylistDisplay final : public QWidget {
    Q_OBJECT
private:
    QListView* playlist_;
    QStringListModel* list_model_;

    void setup();

public:
    explicit QtPlaylistDisplay(QWidget* parent = nullptr);
    void refresh(const std::vector<std::string>& names) const;
    void highlight(int index) const;
    void remove();

signals:
    void selectRequested(int index);
    void removeRequested(int index);
    void dropRequested(const std::vector<std::string>& paths);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};

#endif //QT_PLAYLIST_DISPLAY_H