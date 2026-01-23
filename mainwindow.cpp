#include "mainwindow.h"
#include "ui_main_window.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);

    // Populate language dropdown
    QStringList languages;
    QJsonArray langFiles = QJsonDocument::fromJson(readLanguageFiles()).array();
    for (const QJsonValue &langFile : langFiles) {
        QString language = langFile.toObject().value("language").toString();
        languages.append(language);
    }
    ui->languageDropdown->addItems(languages);

    // Connect buttons to slots
    connect(ui->buildButton, &QPushButton::clicked, this, &MainWindow::on_buildButton_clicked);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::on_runButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buildButton_clicked()
{
    QString language = ui->languageDropdown->currentText();
    QJsonObject langJson = readLanguageConfig(language);
    QString buildCommand = langJson.value("build_command").toString();

    process->start(buildCommand);
    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        ui->outputPanel->append(process->readAllStandardOutput());
    });
}

void MainWindow::on_runButton_clicked()
{
    QString language = ui->languageDropdown->currentText();
    QJsonObject langJson = readLanguageConfig(language);
    QString runCommand = langJson.value("run_command").toString();

    process->start(runCommand);
    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        ui->outputPanel->append(process->readAllStandardOutput());
    });
    connect(process, &QProcess::readyReadStandardError, this, [this]() {
        ui->outputPanel->append(process->readAllStandardError());
    });
}

QByteArray MainWindow::readLanguageFiles()
{
    // Read and return all language JSON files
    QJsonArray langFiles;
    QDirIterator it("path/to/lang", QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QJsonObject langFile = QJsonDocument::fromJson(read_file({it.next()})).object();
        langFiles.append(langFile);
    }
    return QJsonDocument(langFiles).toJson();
}

void MainWindow::loadLanguageConfigurations() {
    QDir langDir("lang");
    QStringList filter("*.json");
    QStringList files = langDir.entryList(filter, QDir::Files);

    for (const QString &file : files) {
        QString filePath = langDir.filePath(file);
        QFile jsonFile(filePath);
        if (jsonFile.open(QFile::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
            if (doc.isObject()) {
                QJsonObject obj = doc.object();

                // Validate required fields
                if (!obj.contains("name") || !obj.contains("file_extension") || 
                    !obj.contains("build") || !obj.contains("run")) {
                    qWarning() << "Invalid language configuration in" << filePath;
                    continue;
                }

                // Add to language selector
                languageSelector->addItem(obj["name"].toString(), file);
            }
            jsonFile.close();
        }
    }
}