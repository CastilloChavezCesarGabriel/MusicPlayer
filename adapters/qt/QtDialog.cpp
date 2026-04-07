#include "QtDialog.h"
#include <QMessageBox>
#include <QFileDialog>

QtDialog::QtDialog(QWidget* parent) : parent_(parent) {}

bool QtDialog::confirm(const std::string& message) {
    return QMessageBox::question(parent_, "",
        QString::fromStdString(message),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

std::string QtDialog::browse() {
    return QFileDialog::getOpenFileName(parent_).toStdString();
}