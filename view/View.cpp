#include "View.h"
#include <QTimer>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QLineEdit>

View::View(QWidget *parent) : QWidget(parent) {
    setupUi();
    setAcceptDrops(true);
}

void View::setupUi() {
    setWindowTitle("Music Player");

    sort_layout_ = new QHBoxLayout();
    sort_by_number_button_ = new QPushButton("Sort by number", this);
    sort_by_name_button_ = new QPushButton("Sort by name", this);
    sort_layout_->addWidget(sort_by_number_button_);
    sort_layout_->addWidget(sort_by_name_button_);
    sort_layout_->setAlignment(Qt::AlignCenter);

    main_layout_ = new QVBoxLayout(this);
    control_layout_ = new QHBoxLayout();
    volume_layout_ = new QHBoxLayout();
    files_layout_ = new QHBoxLayout();

    playlist_view_ = new QListView(this);
    playlist_model_ = new QStringListModel(this);
    playlist_view_->setModel(playlist_model_);

    search_bar_ = new QLineEdit("🔍",this);
    play_button_ = new QPushButton("▶", this);
    pause_button_ = new QPushButton("⏸", this);
    repeat_button_ = new QPushButton("↻", this);
    repeat_button_->setCheckable(true);
    next_button_ = new QPushButton("⏭", this);
    previous_button_ = new QPushButton("⏮", this);
    add_button_ = new QPushButton("✚ Add Song", this);
    remove_button_ = new QPushButton("✖ Remove Song", this);
    skip_button_ = new QPushButton("⏭ Skip Ad", this);
    skip_button_->setVisible(false);

    volume_slider_ = new QSlider(Qt::Horizontal, this);
    volume_slider_->setRange(0, 100);
    volume_slider_->setValue(50);

    volume_label_ = new QLabel("🔊 50%", this);

    control_layout_->addWidget(previous_button_);
    control_layout_->addWidget(play_button_);
    control_layout_->addWidget(pause_button_);
    control_layout_->addWidget(repeat_button_);
    control_layout_->addWidget(next_button_);
    control_layout_->setAlignment(Qt::AlignCenter);

    volume_layout_->addWidget(volume_label_);
    volume_layout_->addWidget(volume_slider_);
    volume_layout_->setAlignment(Qt::AlignCenter);

    files_layout_->addWidget(add_button_);
    files_layout_->addWidget(remove_button_);
    files_layout_->setAlignment(Qt::AlignCenter);

    main_layout_->addLayout(sort_layout_);
    main_layout_->addWidget(search_bar_);
    main_layout_->addWidget(playlist_view_);
    main_layout_->addLayout(control_layout_);
    main_layout_->addLayout(volume_layout_);
    main_layout_->addWidget(skip_button_, 0, Qt::AlignCenter);
    main_layout_->addLayout(files_layout_);

    setLayout(main_layout_);
    setupConnections();
}

void View::setupConnections() {
    auto volume = [this](const int value) {
        emit onVolumeChanged(value);
    };

    auto search = [this](const QString& text) {
        emit onSearchChanged(text);
    };

    connect(play_button_, &QPushButton::clicked, this, &View::onPlayRequested);
    connect(pause_button_, &QPushButton::clicked, this, &View::onPauseRequested);
    connect(repeat_button_, &QPushButton::clicked, this, &View::onRepeatRequested);
    connect(next_button_, &QPushButton::clicked, this, &View::onNextRequested);
    connect(previous_button_, &QPushButton::clicked, this, &View::onPreviousRequested);
    connect(add_button_, &QPushButton::clicked, this, &View::onAddRequested);
    connect(remove_button_, &QPushButton::clicked, this, &View::onRemoveRequested);
    connect(skip_button_, &QPushButton::clicked, this, &View::onSkipAdRequested);
    connect(sort_by_number_button_, &QPushButton::clicked, this, &View::onSortByNumberRequested);
    connect(sort_by_name_button_, &QPushButton::clicked, this, &View::onSortByNameRequested);
    connect(volume_slider_, &QSlider::valueChanged, this, volume);
    connect(search_bar_, &QLineEdit::textChanged, this, search);
}

QListView* View::playlistView() const {
    return playlist_view_;
}

void View::clearSelection() const {
    playlist_view_->clearSelection();
}

void View::enableButtons(const bool enable) const {
    play_button_->setEnabled(enable);
    pause_button_->setEnabled(enable);
    repeat_button_->setEnabled(enable);
    next_button_->setEnabled(enable);
    previous_button_->setEnabled(enable);
    add_button_->setEnabled(enable);
    remove_button_->setEnabled(enable);
    sort_by_number_button_->setEnabled(enable);
    sort_by_name_button_->setEnabled(enable);
}

void View::updatePlaylist(const std::vector<std::string> &songs) const {
    QStringList result;
    for (const auto& song : songs) {
        result.append(QString::fromStdString(song));
    }
    playlist_model_->setStringList(result);
}

void View::updateVolume(const int volume) const {
    volume_label_->setText(QString("🔊 %1%").arg(volume));
}

void View::updateSelection(const int index) const {
    if (!playlist_view_->model())
        return;

    if (index >= 0 && index < playlist_view_->model()->rowCount()) {
        const QModelIndex modelIndex = playlist_view_->model()->index(index, 0);
        playlist_view_->setCurrentIndex(modelIndex);
    }
}

void View::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void View::dropEvent(QDropEvent *event){
    if (const QList<QUrl> urls = event->mimeData()->urls(); !urls.isEmpty()) {
        emit filesDropped(urls);
    }
}

void View::showUserFeedback(const QString &message, const bool success) {
    QMessageBox::information(this, success ? "Success" : "Oops", message);
}

bool View::showConfirmation(const QString &message) {
    const QMessageBox::StandardButton reply = QMessageBox::question(this, "", message,
                                                              QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

void View::showSkipAd(const bool input) const {
    skip_button_->setVisible(input);
}
