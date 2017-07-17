#include "qlocalwid.h"
#include "ui_qlocalwid.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMenu>
#include <QCursor>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>

QLocalWid::QLocalWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QLocalWid)
{
    ui->setupUi(this);
    ui->tableWid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWid->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->LoadBtn,SIGNAL(clicked( )),this,SLOT(LoadSongs()));
    LoadSongsFromDB();
}

QLocalWid::~QLocalWid()
{
    delete ui;
}
void QLocalWid::LoadSongsFromDB()
{
    QSqlQuery query;
    QString name,singer,size,time;
    int i=0;
    query.exec("select * from songtbl");
    if(!query.exec())
    qDebug()<<query.lastError().text();
    while(query.next())
    {
        name=query.value(1).toString();
        singer=query.value(2).toString();
        size=query.value(6).toString();
        time=query.value(5).toString();
        int rownum = ui->tableWid->rowCount();
        ui->tableWid->insertRow(rownum);
        ui->tableWid->setItem(rownum, 0, new QTableWidgetItem(name));
        ui->tableWid->setItem(rownum, 1, new QTableWidgetItem(singer));
        /*ui->tableWid->setItem(i,0,new QTableWidgetItem(name));
        ui->tableWid->setItem(i,1,new QTableWidgetItem(singer));
        ui->tableWid->setItem(i,2,new QTableWidgetItem(time));
        ui->tableWid->setItem(i,3,new QTableWidgetItem(size));*/
        qDebug()<<name<<singer<<endl;
        i++;
        update();
    }
}
void QLocalWid::LoadSongs()
{
    QDB db;
    QStringList pathList = QFileDialog::getOpenFileNames(this, tr("选择文件"), QDir::homePath(), tr("*.mp3"));
    db.LoadSongsFromLocal(pathList);
    LoadSongsFromDB();
}
void QLocalWid::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(tr("删除"),this,SLOT(DelSong()));
    menu.exec(QCursor::pos());
}
void QLocalWid::DelSong()
{
    QDB db;
    QList<QTableWidgetItem*> list=ui->tableWid->selectedItems();
    if(list.size()==0)
        return;
    QTableWidgetItem *item=list[0];
    int index=item->row();
    db.DelSongByName(item->text());
    ui->tableWid->removeRow(index);
}
