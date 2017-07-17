#include "qlrcwnd.h"
#include <QMouseEvent>
#include <QMenu>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QFile>
#include <QIODevice>
#include <QTextCodec>

QLrcWnd::QLrcWnd()
{
    this->setWindowFlags(Qt::SubWindow |Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
    this->resize(1024,60);
    this->setText(tr("For you,Pure Music."));
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明

    this->setCursor(Qt::OpenHandCursor);
    m_Map=new QMap<int,QString>();

    exit = new QAction(tr("隐藏(&D)"),this);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout_slot()));

    this->move(800,800);

    lrcWidth = 0;
}
QLrcWnd::~QLrcWnd()
{
    delete m_Map;
}

void QLrcWnd::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if(event->button() == Qt::MidButton)//点击鼠标滚轮
        close();
    QLabel::mousePressEvent(event);
}

void QLrcWnd::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - dragPosition);
        e->accept();
    }
    QLabel::mouseMoveEvent(e);
}

void QLrcWnd::contextMenuEvent(QContextMenuEvent *ev)
{
    QMenu menu;
    menu.addAction(exit);
    menu.exec(ev->globalPos());
    QLabel::contextMenuEvent(ev);
}

void QLrcWnd::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   // painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //使用该行代码可以实现反锯齿，使歌词显示更漂亮，但是会明显增加CPU占用率
    QFont font(tr("Times New Roman"),30,QFont::Bold);
    painter.setFont(font);
    QLinearGradient lg(0,20,0,50);
    lg.setColorAt(0,QColor(0,170,255,255));
    lg.setColorAt(0.2,QColor(61,214,191,250));
    lg.setColorAt(0.5,QColor(85,255,255,255));
    lg.setColorAt(0.8,QColor(61,214,191,250));
    lg.setColorAt(1,QColor(0,170,255,255));
    painter.setBrush(lg);
    painter.setPen(Qt::NoPen);
    QPainterPath textPath;
    textPath.addText(0,50,font,text());
    painter.drawPath(textPath);

    length = textPath.currentPosition().x();

    painter.setPen(Qt::yellow);
    painter.drawText(0,14,lrcWidth,50,Qt::AlignLeft,text());

}

bool QLrcWnd::showLrcLine(int time)
{
    if(m_Map->contains(time))
    {
        this->setText(m_Map->value(time));
        return true;
    }
    return false;
}

void QLrcWnd::getHeader(const char *str, QString &des)
{
    des = des.remove(str);
    des = des.remove("]");
}

void QLrcWnd::getTime(QString line)
{
    if(line.startsWith("["))
        {
            int index = line.indexOf("]");
            QString t = line.mid(1, index - 1);
            QString mm = t.mid(0,2);
            QString ss = t.mid(3,2);
            //QString ms=  t.mid(6,2);
            int min = mm.toInt();
            int sec = ss.toInt();
            int time = min*60000 + sec*1000;
            t = line.mid(index + 1);
            index = t.lastIndexOf("]");
            if(index < 0)
            {
                m_Map->insert(time, t);
            }
            else
            {
                t = t.mid(index + 1);
                m_Map->insert(time,t);
                getTime(t);
            }
        }
}

void QLrcWnd::init(const QString& fileName)
{
    m_Map->clear();
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QTextStream stream(&file);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    stream.setCodec(codec);
    while(!stream.atEnd())
    {
        QString s = stream.readLine();
        if(s.length()<4)
            continue;
        if(s.startsWith("[ti:"))
        {
            getHeader("[ti:", s);
            m_Map->insert(0, s);
            continue;
        }
        else if(s.startsWith("[ar:"))
        {
            getHeader("[ar:", s);
            m_Map->insert(1000, s);
            continue;
        }
        else if(s.startsWith("[al:"))
        {
            getHeader("[al:", s);
            m_Map->insert(2000, s);
            continue;
        }
        else if(s.startsWith("[by:"))
        {
            getHeader("[by:", s);
            m_Map->insert(3000, s);
            continue;
        }
        else
        {
            getTime(s);
        }
    }
    file.close();
}

void QLrcWnd::timeout_slot()
{
    lrcWidth += length/85;
    update();
}

void QLrcWnd::setLrcWidth()
{
    lrcWidth = 0;
}
