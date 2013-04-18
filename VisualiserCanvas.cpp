#include "VisualiserCanvas.hpp"

#include <QPainter>

VisualiserCanvas::VisualiserCanvas(QWidget *parent) :
	QWidget(parent)
{
	QSizePolicy sp = sizePolicy();
	sp.setHorizontalPolicy(QSizePolicy::Expanding);
	sp.setHeightForWidth(true);
	//sp.setWidthForHeight(true);
	setSizePolicy(sp);
}

int VisualiserCanvas::heightForWidth(int w) const
{
	return w;
}

void VisualiserCanvas::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	qreal scalingFactor = qMin(width()/500., height()/500.);
	p.scale(scalingFactor, scalingFactor);
	p.setBrush(Qt::Dense3Pattern);
	p.drawRect(0,0,500,500);
}
