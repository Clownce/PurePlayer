#ifndef QMYSLIDER_H
#define QMYSLIDER_H

#include <QSlider>
#include <QMouseEvent>

class QMySlider : public QSlider
{
	Q_OBJECT

public:
	QMySlider(QWidget *parent);
	~QMySlider();

private:
	void mousePressEvent(QMouseEvent *e);
	
};

#endif // QMYSLIDER_H
