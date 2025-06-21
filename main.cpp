#include "mainwindow.h"

#include <QApplication>
#include <qstringliteral.h>
#include "utils/templates.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto cpp = LangTemplate(QStringLiteral("cpp"));
    qDebug() << cpp.getDefaultCode();

    MainWindow w;
    w.show();


    return a.exec();
}
