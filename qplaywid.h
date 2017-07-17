#ifndef QPLAYWID_H
#define QPLAYWID_H

#include <QWidget>

class MyItem;
class QGraphicsScene;

namespace Ui {
class QPlayWid;
}

class QPlayWid : public QWidget
{
    Q_OBJECT

public:
    void initText();
    explicit QPlayWid(QWidget *parent = 0);
    ~QPlayWid();

    Ui::QPlayWid *ui;

private:
    MyItem *Item;
    QGraphicsScene *scense;

public:
    void setInfo(QString name,QString singer);
    void tmstart();
    void tmstop();
};

#endif // QPLAYWID_H
