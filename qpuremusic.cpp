#include "qpuremusic.h"
#include "qclosedlg.h"
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenu>
#include <QTime>
#include <QTimer>
#include <QMediaMetaData>
#include <QMap>
#include <QTextBlock>
#include <QColor>
#include <QDebug>
#include <QSqlError>
#include "ui_qplaywid.h"
#include "ui_qlocalwid.h"

QPureMusic::QPureMusic(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon("://QPureMusic/Resources/ICON.ico"));
    trayIcon = new QMySystemTrayIcon(this);
    ui.Volumlabel->setText(QString::number(ui.VolumSlider->value(), 10));
    ui.PlayListFrame->setVisible(false);
    Player = new QMediaPlayer;
    musicPlayList = new QMediaPlaylist;
    musicPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    m_LrcWnd=new QLrcWnd();

    //connect(setDlg, SIGNAL(playlistAdded()), this, SLOT(start()));
    m_Path=new QMap<int,QString>();
    initMusicPlayer();

}

QPureMusic::~QPureMusic()
{
    delete m_Path;
}

void QPureMusic::mousePressEvent(QMouseEvent *e)

{
    if (e->button() == Qt::LeftButton)
        last = e->globalPos();

}



void QPureMusic::mouseMoveEvent(QMouseEvent *e)

{
    if (e->buttons() == Qt::LeftButton){
        int dx = e->globalX() - last.x();

        int dy = e->globalY() - last.y();



        last = e->globalPos();

        move(x() + dx, y() + dy);
    }

}


void QPureMusic::playMusic()
{
    //QMessageBox::about(NULL,"df","你好");
    if (Player->state() == QMediaPlayer::PlayingState)
    {
        ui.PlayButton->setObjectName(QString::fromUtf8("PlayButton"));
        this->pause();

    }
    else if(!musicPlayList->isEmpty())
    {
        m_LrcWnd->setText("Pure Music");
        ui.PlayButton->setObjectName(QString::fromUtf8("PauseButton"));
        this->play();
    }
    QFile qss(":/qss/qpuremusic.qss");
    qss.open(QFile::ReadOnly);
    QString qssstyle = QLatin1String(qss.readAll());
    ui.PlayButton->setStyleSheet(qssstyle);
    qss.close();
}

void QPureMusic::play()
{
    Player->play();
    m_PlayWid->tmstart();
}

void QPureMusic::pause()
{
    Player->pause();
    m_PlayWid->tmstop();
}

int QPureMusic::isAppClose()
{
    QCloseDlg Closedlg(this);
    Closedlg.move((frameGeometry().center().x() - Closedlg.frameGeometry().width() / 2),
                  frameGeometry().center().y() - Closedlg.frameGeometry().height() / 2);
    Closedlg.exec();
    return Closedlg.isAppClose;
}

void QPureMusic::closeEvent(QCloseEvent *e)
{
    //QMessageBox::about(NULL,"df","你好");
    switch (isAppClose())
    {
    case 1:
    {
        hide();
        trayIcon->showMessage(tr("提示"), tr("Pure Music将在后台运行"));
        e->ignore();
        break;
    }
    case 2: e->accept(); break;
    default:e->ignore(); break;
    }
}

Ui::QPureMusicClass QPureMusic::GetUI()
{
    return this->ui;
}

void QPureMusic::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::Trigger:
        if (this->isVisible() == true) {
            ;
        }
        else {
            this->show();
            this->activateWindow();
        }
        break;
    default:
        break;
    }
}

void QPureMusic::VolumChange(int a)
{
    ui.Volumlabel->setText(QString::number(a, 10));
    Player->setVolume(a);
}

void QPureMusic::SetVolum()
{
    int v=Player->volume();
    if(v!=0)
    {
        volume = Player->volume();
        Player->setVolume(0);
        ui.VolumSlider->setValue(0);
        ui.VolumButton->setObjectName(QString::fromUtf8("noVolumButton"));
    }
    else
    {
        Player->setVolume(volume);
        ui.VolumSlider->setValue(volume);
        ui.VolumButton->setObjectName(QString::fromUtf8("VolumButton"));
    }
    QFile qss(":/qss/qpuremusic.qss");
    qss.open(QFile::ReadOnly);
    QString qssstyle = QLatin1String(qss.readAll());
    ui.VolumButton->setStyleSheet(qssstyle);
    qss.close();
}


void QPureMusic::SetDlgisHide()
{
    ui.PlayListFrame->setVisible(ui.PlayListFrame->isHidden());
}

void QPureMusic::CloseSetDlg()
{
    ui.PlayListFrame->setVisible(ui.PlayListFrame->isHidden());
    ui.SetButton->setChecked(!ui.SetButton->isChecked());
}

/*void QPureMusic::start()
{
    Player->setPlaylist(musicPlayList);
    Player->play();
}*/

void QPureMusic::initMusicPlayer()
{
    Player->setPlaylist(musicPlayList);
    volume = ui.VolumSlider->value();
    Player->setVolume(volume);
    //堆栈窗口
    m_ListWid=new QListWidget(this);
    m_ListWid->setObjectName(QStringLiteral("NavListWidget"));
    m_ListWid->insertItem(0,tr("本地音乐"));
    m_LocalWid=new QLocalWid();
    m_ListWid->insertItem(1,tr("正在播放"));
    m_PlayWid=new QPlayWid();
    m_ListWid->insertItem(2,tr("我的收藏"));
    m_FavWid=new QFavWid();

    m_Stack=new QStackedWidget(this);
    m_Stack->addWidget(m_LocalWid);
    m_Stack->addWidget(m_PlayWid);
    m_Stack->addWidget(m_FavWid);
    //QHBoxLayout *mainLayout=new QHBoxLayout(this);
    //ui.mainLayout->setMargin(5);
    //ui.mainLayout->setSpacing(5);
    ui.mainLayout->addWidget(m_ListWid);
    ui.mainLayout->addWidget(m_Stack);
    //ui.mainLayout->addWidget(m_Stack,0,Qt::AlignHCenter);
    m_Stack->setCurrentIndex(1);
    ui.mainLayout->setStretchFactor(m_ListWid,1);
    ui.mainLayout->setStretchFactor(m_Stack,4);
    connect(m_ListWid,SIGNAL(currentRowChanged(int)),m_Stack,SLOT(setCurrentIndex(int)));
    //Player->play();
    connect(Player, SIGNAL(positionChanged(qint64)), this, SLOT(setPosition(qint64)));
    connect(Player, SIGNAL(durationChanged(qint64)), this, SLOT(setDuration(qint64)));
    connect(Player, SIGNAL(metaDataChanged()), this, SLOT(ShowMusicInfo()));
    connect(ui.PlaySlider, SIGNAL(sliderMoved(int)), this, SLOT(setPlayPosition(int)));
    connect(ui.VolumSlider, SIGNAL(valueChanged(int)), this, SLOT(VolumChange(int)));
    connect(ui.ModeButton,SIGNAL(clicked(bool)),this,SLOT(ModeBtn_slot()));//播放模式
    connect(ui.LrcButton,SIGNAL(clicked(bool)),this,SLOT(LrcBtn_slot()));//歌词
    connect(m_LocalWid->ui->PlayAllBtn,SIGNAL(clicked()),this,SLOT(LoadFromLocalAll()));//播放所有本地列表
    connect(ui.SongTableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(playTo(int,int)));
    // connect(setDlg->musicPlayList, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSongList(int)));
}

/*void QPureMusic::updateSongList(int i)
{
    setDlg->GetUI().SongTableWidget->selectRow(i);
    //ui.PlayLabel->setText(tr("正在播放: %1").arg(setDlg->GetUI().SongTableWidget->item(i, 0)->text()));
    //totalTimeValue = Player->metaData(QMediaMetaData::Duration).toInt();
    //ui.PlayLabel->setText(Player->metaData(QMediaMetaData::Title).toString());
}*/

void QPureMusic::playLast()
{
    /*int currentIndex = musicPlayList->currentIndex();
    if (--currentIndex < 0) currentIndex = 0;
    musicPlayList->setCurrentIndex(currentIndex);
    Player->play();*/
    musicPlayList->previous();
}

void QPureMusic::playNext()
{
    /* int currentIndex = musicPlayList->currentIndex();
    if (++currentIndex == musicPlayList->mediaCount()) currentIndex = 0;
    musicPlayList->setCurrentIndex(currentIndex);
    Player->play();*/
    musicPlayList->next();
}

void QPureMusic::setPosition(qint64 pos)
{
    ui.PlaySlider->setValue(pos);

    QTime totalTime(0, (totalTimeValue / 60000) % 60, (totalTimeValue / 1000) % 60);
    QTime currentTime(0, (pos / 60000) % 60, (pos / 1000) % 60);
    QString str = currentTime.toString("mm:ss");
    ui.CurrentTimeLabel->setText(str);
    str = totalTime.toString("mm:ss");
    ui.TotalTimeLabel->setText(str);
    int t = (int)pos;
    t /= 1000;
    t *= 1000;
    if(m_LrcWnd->showLrcLine(t)==true)//歌词移动
    {
        QMap<int,QString>::iterator it;//遍历map
        int index=0;
        for(it=m_LrcWnd->m_Map->begin();it!=m_LrcWnd->m_Map->end();it++)
        {
            if(it.value()==m_LrcWnd->m_Map->value(t))
            {
                QTextCursor curs=m_PlayWid->ui->LrcText->textCursor();
                int pos=m_PlayWid->ui->LrcText->document()->findBlockByNumber(index).position();
                curs.setPosition(pos,QTextCursor::MoveAnchor);
                m_PlayWid->ui->LrcText->setTextCursor(curs);
                //qDebug()<<index<<endl;
                if(index>7)
                {
                    pos=m_PlayWid->ui->LrcText->document()->findBlockByNumber(index+8).position();
                    curs.setPosition(pos,QTextCursor::MoveAnchor);
                    m_PlayWid->ui->LrcText->setTextCursor(curs);
                }
                break;
            }
            index++;
        }
    }

}

void QPureMusic::setDuration(qint64 duration)
{
    ui.PlaySlider->setRange(0, duration);
}

void QPureMusic::ShowMusicInfo()
{
    QString title = Player->metaData(QMediaMetaData::Title).toString();
    QString artist = Player->metaData(QMediaMetaData::Author).toString();
    totalTimeValue = Player->metaData(QMediaMetaData::Duration).toInt();
    m_PlayWid->setInfo(title,artist);

    int index = musicPlayList->currentIndex();
    if (index == -1)
        return;
    ui.SongTableWidget->selectRow(index);
    ui.SongTableWidget->setFocus();
    if(title.isNull()||title.isEmpty())
    {
        QFileInfo fileinfo(m_Path->value(index));
        QString fullname=fileinfo.baseName();
        QString songname,singername;
        if(fullname.contains('-'))
        {
            int index=fullname.indexOf("-");
            songname=fullname.mid(0,index-1);
            singername=fullname.mid(index+1);
        }
        else
        {
            songname=fullname;
            singername=tr("佚名");
        }
        m_PlayWid->setInfo(songname,singername);
    }

    setCurrentLrc(m_Path->value(index));

}

void QPureMusic::setPlayPosition(int pos)
{
    Player->setPosition(pos);
}
//播放模式
void QPureMusic::ModeBtn_slot()
{
    QMenu menu;
    menu.addAction(tr("单曲播放"),this,SLOT(CurrentItemOnce_slot()));
    menu.addAction(tr("单曲循环"),this,SLOT(CurrentItemInLoop_slot()));
    menu.addAction(tr("顺序播放"),this,SLOT(Sequential_slot()));
    menu.addAction(tr("循环播放"),this,SLOT(Loop_slot()));
    menu.addAction(tr("随机播放"),this,SLOT(Random_slot()));
    menu.exec(QCursor::pos());
}
void QPureMusic::CurrentItemOnce_slot()
{
    musicPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}
void QPureMusic::CurrentItemInLoop_slot()
{
    musicPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
}
void QPureMusic::Sequential_slot()
{
    musicPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
}
void QPureMusic::Loop_slot()
{
    musicPlayList->setPlaybackMode(QMediaPlaylist::Loop);
}
void QPureMusic::Random_slot()
{
    musicPlayList->setPlaybackMode(QMediaPlaylist::Random);
}

void QPureMusic::importSongs()
{
    QString initialName = QDir::homePath();
    QStringList pathList = QFileDialog::getOpenFileNames(this, tr("选择文件"), initialName, tr("*.mp3"));


    for (int i = 0; i < pathList.size(); ++i) {
        QString path = QDir::toNativeSeparators(pathList.at(i));
        if (!path.isEmpty()) {
            //QUrl str = QUrl::fromLocalFile(path);
            musicPlayList->addMedia(QUrl::fromLocalFile(path));

            QString fileName = path.split("\\").last();
            int rownum = ui.SongTableWidget->rowCount();
            m_Path->insert(rownum,path);
            ui.SongTableWidget->insertRow(rownum);
            ui.SongTableWidget->setItem(rownum, 0, new QTableWidgetItem(fileName.split(".").front()));
            ui.SongTableWidget->setItem(rownum, 1, new QTableWidgetItem(fileName.split(".").last()));
            //ui.SongTableWidget->setItem(rownum, 2, new QTableWidgetItem(path));
        }
    }
}

void QPureMusic::playTo(int i, int)
{
    if (i >= ui.SongTableWidget->rowCount())
        return;
    musicPlayList->setCurrentIndex(i);
    ui.PlayButton->setObjectName(QString::fromUtf8("PauseButton"));
    this->play();
    QFile qss(":/qss/qpuremusic.qss");
    qss.open(QFile::ReadOnly);
    QString qssstyle = QLatin1String(qss.readAll());
    ui.PlayButton->setStyleSheet(qssstyle);
    qss.close();
}

void QPureMusic::setCurrentLrc(QString path)//设置当前歌词显示
{
    QString lrcName = path.remove(path.right(3)) + "lrc";
    m_LrcWnd->init(lrcName);
    QMap<int,QString>::iterator it;//遍历map
    m_PlayWid->ui->LrcText->clear();
    for(it=m_LrcWnd->m_Map->begin();it!=m_LrcWnd->m_Map->end();it++)
    {
        m_PlayWid->ui->LrcText->append(it.value());
        //m_PlayWid->ui->LrcText->setAlignment(Qt::AlignCenter);//歌词居中
    }
    QTextCursor curs=m_PlayWid->ui->LrcText->textCursor();
    curs.movePosition(QTextCursor::Start);
    m_PlayWid->ui->LrcText->setTextCursor(curs);
}

void QPureMusic::Timeout()//若0.1秒不显示歌词，则显示“Music ...”
{
    if(m_LrcWnd->text().isEmpty())
    {
        m_LrcWnd->setText(tr("未找到歌词！"));
    }
}
void QPureMusic::LrcBtn_slot()
{
    if(ui.LrcButton->isChecked())
        m_LrcWnd->show();
    else
        m_LrcWnd->hide();
}
void QPureMusic::LoadFromLocalAll()
{
    QSqlQuery query;
    QString name,singer,size,time,path;
    query.exec("select * from songtbl");
    if(!query.exec())
    qDebug()<<query.lastError().text();
    while(query.next())
    {
        name=query.value(1).toString();
        singer=query.value(2).toString();
        path=query.value(3).toString();
        size=query.value(6).toString();
        time=query.value(5).toString();
        musicPlayList->addMedia(QUrl::fromLocalFile(path));

        int rownum = ui.SongTableWidget->rowCount();
        m_Path->insert(rownum,path);
        ui.SongTableWidget->insertRow(rownum);
        ui.SongTableWidget->setItem(rownum, 0, new QTableWidgetItem(name));
        ui.SongTableWidget->setItem(rownum, 1, new QTableWidgetItem(singer));
        update();
    }
}
