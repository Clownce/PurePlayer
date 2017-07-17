#include "qclosedlg.h"

QCloseDlg::QCloseDlg(QWidget *parent)
	: MainWindow(parent)
	, isAppClose(0)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	ui.MinRadio->setChecked(true);
}

QCloseDlg::~QCloseDlg()
{
}

void QCloseDlg::mousePressEvent(QMouseEvent *e)

{
	if (e->button() == Qt::LeftButton)
		last = e->globalPos();

}

void QCloseDlg::mouseMoveEvent(QMouseEvent *e)

{
	if (e->buttons() == Qt::LeftButton){
		int dx = e->globalX() - last.x();

		int dy = e->globalY() - last.y();



		last = e->globalPos();

		move(x() + dx, y() + dy);
	}

}

void QCloseDlg::on_okBtnClick(QAbstractButton* btn)
{
	if (btn == ui.OKButton->button((QDialogButtonBox::Ok)))
		if (ui.MinRadio->isChecked())
			isAppClose = 1;
	if (ui.CloseRadio->isChecked())
		isAppClose = 2;
	accept();
}
