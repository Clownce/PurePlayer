#ifndef QPUREMUSIC_H
#define QPUREMUSIC_H

#include <QMainWindow>
#include "ui_qpuremusic.h"
#include "qmysystemtrayicon.h"
#include "qlrcwnd.h"
#include "qlocalwid.h"
#include "qplaywid.h"
#include "qfavwid.h"
#include <QMouseEvent>
#include<QStackedWidget>
#include <QListWidget>
#include <QMap>
class QMediaPlayer;
class QMediaPlaylist;


class QPureMusic : public QMainWindow
{
	Q_OBJECT

public:
	QPureMusic(QWidget *parent = 0);
	~QPureMusic();

private:
	Ui::QPureMusicClass ui;

public:

	void mousePressEvent(QMouseEvent *e);

	void mouseMoveEvent(QMouseEvent *e);

	void closeEvent(QCloseEvent *e);

	int isAppClose();

	Ui::QPureMusicClass GetUI();
private:

	QPoint last;

	QMySystemTrayIcon *trayIcon;

	qint64 totalTimeValue;
    QLrcWnd *m_LrcWnd;//歌词
    QMap<int,QString> *m_Path;//歌曲路径

public:
	QMediaPlayer * Player;
    QMediaPlaylist *musicPlayList;

	void initMusicPlayer();

	int volume;
    void setCurrentLrc(QString path);
    //堆栈窗口
    QStackedWidget *m_Stack;
    QListWidget *m_ListWid;
    QLocalWid *m_LocalWid;
    QPlayWid *m_PlayWid;
    QFavWid *m_FavWid;

public slots:
	void playMusic();
    void play();
    void pause();
	void VolumChange(int);
    void SetVolum();
	void SetDlgisHide();
    void CloseSetDlg();
    //void updateSongList(int);
	void playLast();
	void playNext();
	void setPosition(qint64);
	void setDuration(qint64);
    void ShowMusicInfo();
	void setPlayPosition(int);
    //播放模式
    void ModeBtn_slot();//播放模式
    void CurrentItemOnce_slot();
    void CurrentItemInLoop_slot();
    void Sequential_slot();
    void Loop_slot();
    void Random_slot();
    void importSongs();
    void playTo(int i, int);

private slots:
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
    //void start();
    void Timeout();
    void LrcBtn_slot();
    void LoadFromLocalAll();//加载本地列表全部歌曲
};

#endif // QPUREMUSIC_H
