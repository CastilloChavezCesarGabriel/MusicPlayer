#ifndef QT_PROGRESS_PANEL_H
#define QT_PROGRESS_PANEL_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>

class QtProgressPanel final : public QWidget {
    Q_OBJECT
private:
    QSlider* progress_bar_;
    QLabel* elapsed_time_;
    QLabel* total_time_;

    void setup();
    void wire(QMediaPlayer& media);
    static QString format(qint64 milliseconds);

public:
    QtProgressPanel(QMediaPlayer& media, QWidget* parent = nullptr);
    void enable(bool state) const;
};

#endif //QT_PROGRESS_PANEL_H