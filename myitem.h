#ifndef MYITEM_H
#define MYITEM_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>

class MyItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit MyItem(QObject *parent);
    ~MyItem();

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget = 0);
    QRectF boundingRect () const;

signals:


public slots:



private slots:
    void animateFilp();

private:
    int m_angle;   //rotation angle
    int m_delta;
    QRect prect;
    QTimer tm;

public:
    void tmstart();
    void tmstop();
};

#endif // MYITEM_H
