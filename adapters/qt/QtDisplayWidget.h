#ifndef QT_DISPLAY_WIDGET_H
#define QT_DISPLAY_WIDGET_H

#include "../../view/IDisplayView.h"
#include "../../view/IDisplayControl.h"
#include "QtPlaylistDisplay.h"
#include "QtSortHeader.h"
#include "QtSearchOverlay.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <functional>

class QtDisplayWidget final : public IDisplayView {
private:
    QtPlaylistDisplay* display_;
    QtSortHeader* sort_header_;
    QtSearchOverlay* search_overlay_;
    QLineEdit* search_input_;
    IDisplayControl* listener_ = nullptr;

public:
    QtDisplayWidget(QWidget* parent, QVBoxLayout* layout);
    void wire(IDisplayControl& listener);
    void refresh(const std::vector<std::string>& names) override;
    void highlight(int index) override;
    void suggest(const std::vector<std::string>& names) override;
    void dismiss() override;
    void sort(const std::string& label) override;
    void remove() const;
    void onSelect(const std::function<void(int)>& callback) const;
    void onRemoveRequest(const std::function<void(int)>& callback) const;
    void onDrop(const std::function<void(const std::vector<std::string>&)>& callback) const;
};

#endif //QT_DISPLAY_WIDGET_H
