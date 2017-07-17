#include "qdb.h"
#include <QMessageBox>
#include <QSqlError>
#include <QtSql>
#include <QPluginLoader>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>

QDB::QDB()
{
    CreateTable();
}
bool QDB::CreateConnection()
{
    QSqlDatabase m_DB=QSqlDatabase::addDatabase("QSQLITE");
    m_DB.setDatabaseName("PureMusic.db");
    if(!m_DB.open())
    {
        qDebug()<<"Failed to connect the database!";
        return false;
    }
    return true;
}
void QDB::CreateTable()
{
    QSqlQuery query;
    //歌曲表：ID、歌曲名、歌手、路径、专辑ID、时长、大小、发布时间、标签
    query.exec("create table if not exists SongTBL(SongID integer primary key autoincrement,Name varchar(32),Singer varchar(32),Path varchar(64),AlbumID integer,Time varchar(20),Size varchar(10),Release varchar(20),Tag varchar(64))");
    //收藏列表：列表名、歌曲ID
    query.exec("create table if not exists FavListTBL(Name varchar(32) primary key,SongID integer)");
    //专辑：专辑ID、专辑名、歌手、发布时间、简介
    query.exec("create table if not exists AlbumTBL(AlbumID integer primary key autoincrement,Name varchar(32),SingerID integer,Release varchar(20),Note varchar(64))");
    //歌手：歌手ID、歌手名、出生地、出生日期、简介
    query.exec("create table if not exists SingerTBL(SingerID integer primary key autoincrement,Name varchar(32),Area varchar(20),Birth varchar(20),Note varchar(64)");
    qDebug()<<query.lastError().text();
}

void QDB::LoadSongsFromLocal(QStringList pathlist)
{
    QStringList pathList = pathlist;
    CreateTable();
    if(pathList.count()>0)
    {
        foreach (QString path, pathList)
        {
            if(!path.isEmpty())
            {
                QFileInfo fileinfo(path);
                QString fullname=fileinfo.baseName();
                QString songname,singername;
                if(fullname.contains('-'))
                {
                    int index=fullname.indexOf("-");
                    songname=fullname.mid(0,index-1);
                    singername=fullname.mid(index+1);
                }
                else
                {
                    songname=fullname;
                    singername=tr("佚名");
                }
                QSqlQuery query;
                query.prepare("insert into songtbl (name,singer,path) values (?,?,?)");
                query.addBindValue(songname);
                query.addBindValue(singername);
                query.addBindValue(path);
                if(!query.exec())
                qDebug()<<query.lastError().text();
            }
        }
    }
}
void QDB::DelSongByName(QString name)
{
    QSqlQuery query;
    query.prepare("drop * from songtbl where Name=='?'");
    query.addBindValue(name);
    query.exec();
}
