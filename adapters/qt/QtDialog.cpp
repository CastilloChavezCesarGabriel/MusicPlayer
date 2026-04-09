#include "QtDialog.h"
#include <QMessageBox>
#include <QFileDialog>

QtDialog::QtDialog(QWidget* parent) : parent_(parent) {}

bool QtDialog::confirm(const std::string& message) const {
    return QMessageBox::question(parent_, "",
        QString::fromStdString(message),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

std::string QtDialog::browse() const {
    return QFileDialog::getOpenFileName(parent_).toStdString();
}