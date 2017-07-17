#include <QApplication>
#include <QFile>
#include "qpuremusic.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase m_DB=QSqlDatabase::addDatabase("QSQLITE");
    m_DB.setDatabaseName("PureMusic.db");
    if(!m_DB.open())
    {
        qDebug()<<"Failed to connect the database!";
    }
    QFile qss(":/qss/qpuremusic.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    qss.close();
    QPureMusic mainWindow;
    mainWindow.show();
    return a.exec();
}
