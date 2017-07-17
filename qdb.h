#ifndef QDB_H
#define QDB_H
#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class QDB:public QObject
{
    Q_OBJECT
public:
    QDB();
    bool CreateConnection();
    void CreateTable();
    void LoadSongsFromLocal(QStringList pathlist);
    void DelSongByName(QString name);
};

#endif // QDB_H
