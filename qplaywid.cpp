#include "qplaywid.h"
#include "myitem.h"
#include "ui_qplaywid.h"

QPlayWid::QPlayWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QPlayWid)
{
    ui->setupUi(this);
    ui->LrcText->setReadOnly(true);
    Item=new MyItem(ui->DiscGraphics);
    scense=new QGraphicsScene;
    ui->DiscGraphics->setScene(scense);
    scense->addItem(Item);
}

QPlayWid::~QPlayWid()
{
    delete ui;
}

void QPlayWid::tmstart()
{
    Item->tmstart();
}

void QPlayWid::tmstop()
{
    Item->tmstop();
}
void QPlayWid::setInfo(QString name, QString singer)
{
    ui->NameLbl->setText(name);
    ui->SingerLbl->setText(singer);
}
