#ifndef QLRCWND_H
#define QLRCWND_H

#include <QLabel>
#include <QTimer>
#include <QMap>

class QLrcWnd : public QLabel
{
    Q_OBJECT

public:
    QLrcWnd();
    ~QLrcWnd();
    QAction *exit;
    void setTime(int num){time = num;}
    void setLrcWidth();
    QTimer *timer;
    QMap<int,QString> *m_Map;
    bool showLrcLine(int time);//显示某行歌词
    void getHeader(const char *str, QString &des);
    void getTime(QString line);
    void init(const QString &fileName);
private:
    QPoint dragPosition;
    int time;
    qreal length;
    qreal lrcWidth;
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *ev);
    void paintEvent(QPaintEvent *);

private slots:
    void timeout_slot();
};

#endif // QLRCWND_H
