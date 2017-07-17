#include "qmygraphicsview.h"
#include "qpuremusic.h"
#include "qclosedlg.h"

QMyGraphicsView::QMyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{

}

QMyGraphicsView::~QMyGraphicsView()
{

}

void QMyGraphicsView::mousePressEvent(QMouseEvent *e)

{
	if (parent()->objectName() == QString::fromUtf8("centralWidget"))
		((QPureMusic *)parent())->mousePressEvent(e);
	if (parent()->objectName() == QString::fromUtf8("QCloseDlg"))
		((QCloseDlg *)parent())->mousePressEvent(e);
}



void QMyGraphicsView::mouseMoveEvent(QMouseEvent *e)

{
	if (parent()->objectName() == QString::fromUtf8("centralWidget"))
		((QPureMusic *)parent())->mouseMoveEvent(e);
	if (parent()->objectName() == QString::fromUtf8("QCloseDlg"))
		((QCloseDlg *)parent())->mouseMoveEvent(e);
}
