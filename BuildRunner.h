#ifndef BUILDRUNNER_H
#define BUILDRUNNER_H

#include <QObject>
#include <QPushButton>
#include <QTextEdit>

class BuildRunner : public QObject {
    Q_OBJECT

public:
    explicit BuildRunner(QPushButton *buildButton, QPushButton *runButton, QTextEdit *outputPanel, QObject *parent = nullptr);

signals:
    void buildStarted();
    void runStarted();

private slots:
    void onBuildButton_clicked();
    void onRunButton_clicked();

private:
    QPushButton *buildButton;
    QPushButton *runButton;
    QTextEdit *outputPanel;

    QByteArray getBuildCMD();
    QByteArray getRunCMD();
};

#endif // BUILDRUNNER_H
