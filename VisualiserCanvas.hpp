#ifndef VISUALISERCANVAS_HPP
#define VISUALISERCANVAS_HPP

#include <QWidget>
#include "World.hpp"

#define LEG1COLOR Qt::red
#define LEG2COLOR Qt::magenta

class Visualiser;

class VisualiserCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit VisualiserCanvas(QWidget *parent);

	int heightForWidth(int w) const;

protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *e);

	void mouseMoveEvent(QMouseEvent *e);
	void leaveEvent(QEvent *);
	void mouseReleaseEvent(QMouseEvent *);
signals:
	
public slots:
	void setLastGauge(qreal);

private:
	qreal lastGauge;
	bool mouseIn;
	QPointF mousePosition;
};

#endif // VISUALISERCANVAS_HPP
