#include "myitem.h"

MyItem::MyItem(QObject *parent)
    : QObject(parent)
{
    m_angle = 0;
    m_delta = 1;
    prect.setWidth(185);
    prect.setHeight(185);
    //tm.start(30);
    connect(&tm,SIGNAL(timeout()),this,SLOT(animateFilp()));
    //animateFilp();
}

MyItem::~MyItem()
{

}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap bg;
    bg.load(":/QPureMusic/Resources/psd9397.png");
    painter->drawPixmap(QRect(0,0,prect.width(),prect.height()),bg);
}

QRectF MyItem::boundingRect() const
{
    return QRectF(0,0,prect.width(),prect.height());
}

void MyItem::animateFilp()
{
    m_angle += m_delta;
    m_angle = m_angle%360;

    QRectF r = boundingRect();
    setTransform(QTransform()
                 .translate(r.width() / 2, r.height() /2)
                 .rotate(m_angle, Qt::ZAxis)
                 .translate(-r.width() / 2, -r.height() / 2));

    //QTimer::singleShot(30, this, SLOT(animateFilp()));
}

void MyItem::tmstart()
{
    tm.start(30);
}

void MyItem::tmstop()
{
    tm.stop();
}
