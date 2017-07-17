#ifndef QMYSYSTEMTRAYICON_H
#define QMYSYSTEMTRAYICON_H

#include <QSystemTrayIcon>

class QAction;
class QMenu;

class QMySystemTrayIcon : public QSystemTrayIcon
{
	Q_OBJECT

public:
	QMySystemTrayIcon(QObject *parent);
	~QMySystemTrayIcon();

private:
	QAction *restoreAction;
	QAction *quitAction;

	QMenu *trayContextMenu;

private:
	void createSystemTrayIcon();

	
};

#endif // QMYSYSTEMTRAYICON_H
