#ifndef QCLOSEDLG_H
#define QCLOSEDLG_H

#include <QDialog>
#include "ui_qclosedlg.h"
#include <QMouseEvent>

class QCloseDlg : public QDialog
{
	Q_OBJECT

public:
	QCloseDlg(QWidget *parent /*= 0*/);
	~QCloseDlg();

private:
	Ui::QCloseDlg ui;

public:

	void mousePressEvent(QMouseEvent *e);

	void mouseMoveEvent(QMouseEvent *e);

private:

	QPoint last;

	QWidget *MainWindow;

public slots:
	void on_okBtnClick(QAbstractButton*);

public:
	int isAppClose;
};

#endif // QCLOSEDLG_H
