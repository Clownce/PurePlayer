#ifndef QLOCALWID_H
#define QLOCALWID_H

#include <QWidget>
#include "qdb.h"
#include <QContextMenuEvent>

namespace Ui {
class QLocalWid;
}

class QLocalWid : public QWidget
{
    Q_OBJECT

public:
    void contextMenuEvent(QContextMenuEvent *event);
    explicit QLocalWid(QWidget *parent = 0);
    ~QLocalWid();

    Ui::QLocalWid *ui;
    void LoadSongsFromDB();
private slots:
    void LoadSongs();
    void DelSong();
};

#endif // QLOCALWID_H
