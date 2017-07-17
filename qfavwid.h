#ifndef QFAVWID_H
#define QFAVWID_H

#include <QWidget>
#include <QContextMenuEvent>

namespace Ui {
class QFavWid;
}

class QFavWid : public QWidget
{
    Q_OBJECT

public:
    void contextMenuEvent(QContextMenuEvent *event);
    explicit QFavWid(QWidget *parent = 0);
    ~QFavWid();

private:
    Ui::QFavWid *ui;
public slots:
    void AddCollection();
    void DelCollection();
};

#endif // QFAVWID_H
