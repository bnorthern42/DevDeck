#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QTextEdit>

class FileHandler : public QObject {
    Q_OBJECT

public:
    explicit FileHandler(QTextEdit *codeEditor, QObject *parent = nullptr);

signals:
    void fileSaved();

private slots:
    void onOpenFile();
    void onSaveFile();

private:
    QTextEdit *codeEditor;
};

#endif // FILEHANDLER_H
