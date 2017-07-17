#include "qfavwid.h"
#include "ui_qfavwid.h"
#include <QMenu>
#include <QCursor>
#include <QSqlQuery>

QFavWid::QFavWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFavWid)
{
    ui->setupUi(this);
    ui->horizontalLayout->setStretch(0,1);
    ui->horizontalLayout->setStretch(1,5);
    QSqlQuery query;
    query.exec("select * from favlisttbl");
    while(query.next())
    {
        int currow=ui->m_FavList->count();
        ui->m_FavList->insertItem(currow,query.value(0).toString());
    }
}

QFavWid::~QFavWid()
{
    delete ui;
}
void QFavWid::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(tr("添加"),this,SLOT(AddCollection()));
    menu.addAction(tr("删除"),this,SLOT(DelCollection()));
    menu.exec(QCursor::pos());
}
void QFavWid::AddCollection()
{
    int index=ui->m_FavList->count();
    ui->m_FavList->insertItem(index,tr("新的收藏"));
}
void QFavWid::DelCollection()
{
    QList<QListWidgetItem *> list=ui->m_FavList->selectedItems();
    if(list.size()==0)
        return;
    QListWidgetItem *item=list[0];
    delete item;
}
