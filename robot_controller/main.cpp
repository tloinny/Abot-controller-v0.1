#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile qss(":/qss/darkgray.css");
           if(qss.open(QFile::ReadOnly))
           {
               qDebug("open success");
               QString style = QLatin1String(qss.readAll());
               app.setStyleSheet(style);
               qss.close();
           }
           else
           {
              qDebug("Open failed");
           }
    MainWindow* mainWindow = new MainWindow("Robot arm controller v0.1");
    return app.exec();
}
