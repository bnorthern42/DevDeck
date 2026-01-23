#include "FileHandler.h"
#include <QFileDialog>
#include <QMessageBox>

FileHandler::FileHandler(QTextEdit *codeEditor, QWidget *parent) : QObject(parent), codeEditor(codeEditor), parentWidget(parent), currentFilePath("") {
}

QString FileHandler::getCurrentFilePath() const {
    return currentFilePath;
}

void FileHandler::onOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(parentWidget, "Open File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            codeEditor->setPlainText(file.readAll());
            currentFilePath = fileName;
            emit fileLoaded();
            file.close();
        }
    }
}

void FileHandler::onSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(parentWidget, "Save File", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(codeEditor->toPlainText().toUtf8());
            currentFilePath = fileName;
            emit fileSaved();
            file.close();
        }
    }
}
