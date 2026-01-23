#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadLanguageConfigurations();
    connect(ui->languageSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_languageSelector_currentIndexChanged);
    connect(ui->buildButton, &QPushButton::clicked, this, &MainWindow::on_buildButton_clicked);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::on_runButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    // Execute the build command
    QProcess process;
    process.start(buildCMD);
    process.waitForFinished();
    QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
    ui->outputPanel->setText(output);
}

void MainWindow::on_runButton_clicked()
{
    if (currentLanguage.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a language first.");
        return;
    }
    QByteArray runCMD = getRunCMD();
    // Execute the run command
    QProcess process;
    process.start(runCMD);
    process.waitForFinished();
    QString output = process.readAllStandardOutput() + "\n" + process.readAllStandardError();
    ui->outputPanel->setText(output);
}

void MainWindow::loadLanguageConfigurations(const QString &language)
{
    currentLanguage = language;
    QDir langDir("lang");
    QStringList filter("*.json");
    QStringList files = langDir.entryList(filter, QDir::Files);

    for (const QString &file : files) {
        if (file.startsWith(language)) {
            QString filePath = langDir.filePath(file);
            QFile jsonFile(filePath);
            if (jsonFile.open(QFile::ReadOnly)) {
                QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
                if (doc.isObject()) {
                    QJsonObject obj = doc.object();
                    ui->buildButton->setText(obj["buildCMD"].toString());
                    ui->runButton->setText(obj["runCMD"].toString());
                    break;
                }
            }
        }
    }
}

QByteArray MainWindow::getBuildCMD()
{
    if (currentLanguage.isEmpty()) {
        return QByteArray();
    }
    QDir langDir("lang");
    QString filePath = langDir.filePath(currentLanguage + ".json");
    QFile jsonFile(filePath);
    if (jsonFile.open(QFile::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            return obj["buildCMD"].toString().toUtf8();
        }
    }
    return QByteArray();
}

QByteArray MainWindow::getRunCMD()
{
    if (currentLanguage.isEmpty()) {
        return QByteArray();
    }
    QDir langDir("lang");
    QString filePath = langDir.filePath(currentLanguage + ".json");
    QFile jsonFile(filePath);
    if (jsonFile.open(QFile::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            return obj["runCMD"].toString().toUtf8();
        }
    }
    return QByteArray();
}
