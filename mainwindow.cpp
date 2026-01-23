#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDir>
#include <QTemporaryFile>
#include <QDebug>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QPushButton>
#include <QComboBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_MainWindow), isDirty(false)
{
    ui->setupUi(this);
    
    // Use the codeEditor from the UI file
    codeEditor = ui->codeEditor;

    fileHandler = new FileHandler(codeEditor, this);

    loadLanguageConfigurations();
    
    // Manual connections removed because on_objectName_signalName slots are auto-connected by setupUi
    
    openAction = new QAction("Open", this);
    saveAction = new QAction("Save", this);
    menuBar()->addAction(openAction);
    menuBar()->addAction(saveAction);
    
    connect(openAction, &QAction::triggered, fileHandler, &FileHandler::onOpenFile);
    connect(saveAction, &QAction::triggered, fileHandler, &FileHandler::onSaveFile);
    
    connect(fileHandler, &FileHandler::fileLoaded, this, &MainWindow::onFileLoaded);
    connect(fileHandler, &FileHandler::fileSaved, this, &MainWindow::onFileSaved);
}

MainWindow::~MainWindow()
{
    delete ui;
    // fileHandler is a child of MainWindow (passed 'this' as parent), so it will be deleted automatically.
}

void MainWindow::loadLanguageConfigurations()
{
    QDir langDir("lang");
    QStringList filter("*.json");
    QStringList files = langDir.entryList(filter, QDir::Files);

    for (const QString &file : files) {
        if (file.contains(".json")) {
            QString languageName = file.left(file.indexOf('.'));
            ui->languageSelector->addItem(languageName);
        }
    }

    // Validate required fields
    if (ui->languageSelector->count() == 0) {
        QMessageBox::warning(this, "Error", "No language configurations found.");
        ui->buildButton->setEnabled(false);
        ui->runButton->setEnabled(false);
    } else {
        ui->buildButton->setEnabled(true);
        ui->runButton->setEnabled(true);
    }
}

void MainWindow::on_languageSelector_currentIndexChanged(int index)
{
    QString selectedLanguage = ui->languageSelector->itemText(index);
    loadLanguageConfigurations(selectedLanguage);
}

void MainWindow::on_buildButton_clicked()
{
    if (currentLanguage.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a language first.");
        return;
    }
    QByteArray buildCMD = getBuildCMD();
    if (buildCMD.isEmpty()) return;

    // Execute the build command
    QProcess process;
    process.start(buildCMD);
    process.waitForFinished();
    QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
    appendTimestampedOutput(output, true);
}

void MainWindow::on_runButton_clicked()
{
    if (currentLanguage.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a language first.");
        return;
    }
    QByteArray runCMD = getRunCMD();
    if (runCMD.isEmpty()) return;

    // Execute the run command
    QProcess process;
    process.start(runCMD);
    process.waitForFinished();
    QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
    appendTimestampedOutput(output, false);
}

void MainWindow::on_clearOutputButton_clicked()
{
    ui->outputPanel->clear();
}

void MainWindow::onFileLoaded()
{
    isDirty = false;
}

void MainWindow::onFileSaved()
{
    isDirty = false;
}

void MainWindow::loadLanguageConfigurations(const QString &language)
{
    currentLanguage = language;
    currentTemplate = LangTemplate(language);
    
    ui->buildButton->setToolTip(currentTemplate.getBuildCMD());
    ui->runButton->setToolTip(currentTemplate.getRunCMD());
    
    if (codeEditor->toPlainText().isEmpty()) {
        codeEditor->setPlainText(currentTemplate.getDefaultCode());
    }
}

QByteArray MainWindow::getBuildCMD()
{
    if (currentLanguage.isEmpty()) {
        return QByteArray();
    }
    
    QString filePath = fileHandler->getCurrentFilePath();
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please save the file before building.");
        return QByteArray();
    }

    QFileInfo fileInfo(filePath);
    QString filename = fileInfo.absoluteFilePath();
    QString basename = fileInfo.baseName(); // Filename without extension
    // Note: baseName() returns "foo" for "foo.tar.gz". completeBaseName() returns "foo.tar".
    // For "main.cpp", baseName is "main".
    
    QString cmd = currentTemplate.getBuildCMD();
    cmd.replace("{filename}", filename);
    cmd.replace("{basename}", basename);
    
    return cmd.toUtf8();
}

QByteArray MainWindow::getRunCMD()
{
    if (currentLanguage.isEmpty()) {
        return QByteArray();
    }
    
    QString filePath = fileHandler->getCurrentFilePath();
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please save the file before running.");
        return QByteArray();
    }

    QFileInfo fileInfo(filePath);
    QString filename = fileInfo.absoluteFilePath();
    QString basename = fileInfo.baseName();
    
    QString cmd = currentTemplate.getRunCMD();
    cmd.replace("{filename}", filename);
    cmd.replace("{basename}", basename);
    
    return cmd.toUtf8();
}

void MainWindow::appendTimestampedOutput(const QString &text, bool isBuild)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString prefix = isBuild ? "[BUILD]" : "[RUN]";
    QString formattedOutput = QString("[%1] %2:\n%3\n").arg(timestamp, prefix, text);
    ui->outputPanel->append(formattedOutput);
}
