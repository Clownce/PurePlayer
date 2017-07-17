#include "qmyslider.h"

QMySlider::QMySlider(QWidget *parent)
	: QSlider(parent)
{

}

QMySlider::~QMySlider()
{

}

void QMySlider::mousePressEvent(QMouseEvent *e)
{
	QSlider::mousePressEvent(e);
	if (orientation() == Qt::Horizontal)
	{
		double pos = e->pos().x() / (double)width();
		setValue(pos * (maximum() - minimum()) + minimum());
	}
	if (orientation() == Qt::Vertical)
	{
		double pos = e->pos().y() / (double)height();
		setValue(((double)1 - pos) * (maximum() - minimum()) + minimum());
	}
}
