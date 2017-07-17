#include "qmysystemtrayicon.h"
#include "qpuremusic.h"
#include <QAction>
#include <QMenu>

QMySystemTrayIcon::QMySystemTrayIcon(QObject *parent)
	: QSystemTrayIcon(parent)
{
	createSystemTrayIcon();
}

QMySystemTrayIcon::~QMySystemTrayIcon()
{

}

void QMySystemTrayIcon::createSystemTrayIcon()
{
	setIcon(QIcon(tr(":/QPureMusic/Resources/ICON.ico")));
	setToolTip(tr("Pure Music"));

    restoreAction = new QAction(tr("打开主面板"), this);
	connect(restoreAction, SIGNAL(triggered()), (QPureMusic *)parent(), SLOT(show()));

    quitAction = new QAction(tr("退出"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	trayContextMenu = new QMenu((QWidget *)parent());
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_SongList);
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Import);
	trayContextMenu->addSeparator();
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Last);
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Play);
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Stop);
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Next);
	trayContextMenu->addSeparator();
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_Support);
	trayContextMenu->addAction(((QPureMusic *)parent())->GetUI().action_About);
	trayContextMenu->addSeparator();
	trayContextMenu->addAction(restoreAction);
	trayContextMenu->addAction(quitAction);
	setContextMenu(trayContextMenu);

	show();
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		(QPureMusic *)parent(), SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
