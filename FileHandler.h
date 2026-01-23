#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>

class FileHandler : public QObject {
    Q_OBJECT

public:
    explicit FileHandler(QTextEdit *codeEditor, QWidget *parent = nullptr);
    QString getCurrentFilePath() const;

public slots:
    void onOpenFile();
    void onSaveFile();

signals:
    void fileSaved();
    void fileLoaded();

private:
    QTextEdit *codeEditor;
    QWidget *parentWidget;
    QString currentFilePath;
};

#endif // FILEHANDLER_H
