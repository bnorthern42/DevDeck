#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QToolBar>
#include "FileHandler.h"
#include "utils/templates.hpp"

class Ui_MainWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_languageSelector_currentIndexChanged(int index);
    void on_buildButton_clicked();
    void on_runButton_clicked();
    void on_clearOutputButton_clicked();
    void onFileLoaded();
    void onFileSaved();

private:
    Ui_MainWindow *ui;
    QTextEdit *codeEditor;
    QAction *openAction;
    QAction *saveAction;
    bool isDirty;
    QString currentLanguage;
    FileHandler *fileHandler;
    LangTemplate currentTemplate;

    void loadLanguageConfigurations();
    void loadLanguageConfigurations(const QString &language);
    QByteArray getBuildCMD();
    QByteArray getRunCMD();
    void appendTimestampedOutput(const QString &text, bool isBuild);
};

#endif // MAINWINDOW_H
