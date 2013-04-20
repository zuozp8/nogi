#include "VisualiserCanvas.hpp"
#include "Visualiser.hpp"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

VisualiserCanvas::VisualiserCanvas(QWidget *parent) :
	QWidget(parent)
{
	QSizePolicy sp = sizePolicy();
	sp.setHorizontalPolicy(QSizePolicy::Expanding);
	sp.setHeightForWidth(true);
	//sp.setWidthForHeight(true);
	setSizePolicy(sp);
	mouseIn = false;
	setMouseTracking(true);
}

int VisualiserCanvas::heightForWidth(int w) const
{
	return w / qreal(WORLD->dimenstions().x()) * WORLD->dimenstions().y();
}

void VisualiserCanvas::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	qreal scalingFactor = qMin(width()/qreal(WORLD->dimenstions().x()),
														 height()/qreal(WORLD->dimenstions().y()));
	p.scale(scalingFactor, scalingFactor);
	p.setClipRect(QRect(QPoint(), WORLD->dimenstions()));

	//BACKGROUND
	p.setBrush(Qt::SolidPattern);
	p.drawRect(0, 0, WORLD->dimenstions().x(), WORLD->dimenstions().y());

	//FOGS
	p.setBrush(QBrush(Qt::white, Qt::Dense2Pattern));
	p.setPen(QColor(Qt::white));
	foreach (World::Fog fog, WORLD->fogs()) {
		p.setOpacity(fog.density);
		p.drawEllipse(fog.position, fog.r, fog.r);
	}

	//MOUSE
	if (mouseIn) {
		if (VISUALISER->ui->fogRadioButton->isChecked()) {
			p.setBrush(QBrush(Qt::white, Qt::Dense3Pattern));
			p.setPen(QColor(Qt::white));
			p.setOpacity(VISUALISER->ui->fogDensity->value());
			int radius = VISUALISER->ui->fogRadius->value();
			p.drawEllipse(mousePosition, radius, radius);
		} else {
			p.setOpacity(0.6);
			p.setBrush(QBrush(
									 VISUALISER->ui->leg1RadioButton->isChecked() ? LEG1COLOR : LEG2COLOR,
									 Qt::Dense3Pattern));
			p.drawEllipse(mousePosition, 8, 8);
		}
		p.setOpacity(1);
	}

	//LEGS
	QPair<QPointF, QPointF> robotPosition = WORLD->robotPosition();
	p.setPen(QColor(Qt::white));
	p.setBrush(QBrush(LEG1COLOR));
	p.drawEllipse(robotPosition.first, 8, 8);

	p.setBrush(QBrush(LEG2COLOR));
	p.drawEllipse(robotPosition.second, 8, 8);
}

void VisualiserCanvas::resizeEvent(QResizeEvent *e)
{
	qDebug() << e->size();
	QWidget::resizeEvent(e);
}

void VisualiserCanvas::mouseMoveEvent(QMouseEvent *e)
{
	qreal scalingFactor = qMin(width()/qreal(WORLD->dimenstions().x()),
														 height()/qreal(WORLD->dimenstions().y()));
	if (e->pos().x() > WORLD->dimenstions().x() * scalingFactor ||
			e->pos().y() > WORLD->dimenstions().y() * scalingFactor ) {
		if (mouseIn)
			update();
		mouseIn = false;
		return;
	}
	mouseIn = true;
	mousePosition = e->posF()/scalingFactor;
	update();
}

void VisualiserCanvas::leaveEvent(QEvent *)
{
	mouseIn = false;
	update();
}

void VisualiserCanvas::mouseReleaseEvent(QMouseEvent *)
{
	if (mouseIn) {
		if (VISUALISER->ui->fogRadioButton->isChecked()) {
			WORLD->addFog({mousePosition,
										 VISUALISER->ui->fogRadius->value(),
										 VISUALISER->ui->fogDensity->value()});
		} else if (VISUALISER->ui->leg1RadioButton->isChecked()) {
			WORLD->setLeg1Posision(mousePosition);
		} else {
			WORLD->setLeg2Posision(mousePosition);
		}
	}
	update();
}
