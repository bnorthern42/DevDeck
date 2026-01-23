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
    void onOpenFile();
    void onSaveFile();

private:
    Ui_MainWindow *ui;
    QTextEdit *codeEditor;
    QComboBox *languageSelector;
    QMenuBar *menuBar;
    QToolBar *toolbar;
    QAction *openAction;
    QAction *saveAction;
    bool isDirty;
};

#endif // MAINWINDOW_H
