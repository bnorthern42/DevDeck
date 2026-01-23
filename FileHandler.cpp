#include "FileHandler.h"
#include <QFileDialog>
#include <QMessageBox>

FileHandler::FileHandler(QTextEdit *codeEditor, QObject *parent) : QObject(parent), codeEditor(codeEditor) {
    connect(openAction, &QAction::triggered, this, &FileHandler::onOpenFile);
    connect(saveAction, &QAction::triggered, this, &FileHandler::onSaveFile);
}

void FileHandler::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            codeEditor->setPlainText(file.readAll());
            isDirty = false;
            file.close();
        }
    }
}

void FileHandler::onSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(codeEditor->toPlainText().toUtf8());
            isDirty = false;
            emit fileSaved();
            file.close();
        }
    }
}
