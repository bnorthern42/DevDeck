#include "BuildRunner.h"
#include <QProcess>
#include <QDebug>

BuildRunner::BuildRunner(QPushButton *buildButton, QPushButton *runButton, QTextEdit *outputPanel, QObject *parent) : QObject(parent), buildButton(buildButton), runButton(runButton), outputPanel(outputPanel) {
    connect(buildButton, &QPushButton::clicked, this, &BuildRunner::onBuildButton_clicked);
    connect(runButton, &QPushButton::clicked, this, &BuildRunner::onRunButton_clicked);
}

void BuildRunner::onBuildButton_clicked() {
    QByteArray buildCMD = getBuildCMD();
    if (!buildCMD.isEmpty()) {
        QProcess process;
        process.start(buildCMD);
        process.waitForFinished();
        QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
        outputPanel->append(output);
    }
}

void BuildRunner::onRunButton_clicked() {
    QByteArray runCMD = getRunCMD();
    if (!runCMD.isEmpty()) {
        QProcess process;
        process.start(runCMD);
        process.waitForFinished();
        QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
        outputPanel->append(output);
    }
}

QByteArray BuildRunner::getBuildCMD() {
    // Implement logic to get build command
    return QByteArray();
}

QByteArray BuildRunner::getRunCMD() {
    // Implement logic to get run command
    return QByteArray();
}
