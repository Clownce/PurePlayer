#ifndef QMYGRAPHICSVIEW_H
#define QMYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class QMyGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	QMyGraphicsView(QWidget *parent);
	~QMyGraphicsView();

protected:

	void mousePressEvent(QMouseEvent *e);

	void mouseMoveEvent(QMouseEvent *e);

private:

	QPoint last;

	
};

#endif // QMYGRAPHICSVIEW_H
