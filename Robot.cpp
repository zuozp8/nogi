#include "Robot.hpp"
#include "Visualiser.hpp"
#include <QDebug>
#include <QDebug>

Robot::Robot(QObject *parent) :
	QObject(parent)
{
}

void Robot::step()
{
	int val1, val2;

	if(VISUALISER->ui->controlDirections->isChecked()){
		val1 = VISUALISER->ui->direction1->value();
		val2 = VISUALISER->ui->direction2->value();
	}else{
		val1 = 180;
		val2 = 180;
	}

	qreal pi = 3.1415;

	qreal alfa1 = 2.0*pi*(qreal(val1)/360.0);
	qreal alfa2 = 2.0*pi*(qreal(val2)/360.0);

	qreal dx1 = -sin(alfa1);
	qreal dy1 = cos(alfa1);

	qreal dx2 = -sin(alfa2);
	qreal dy2 = cos(alfa2);

	emit moves(QPointF(dx1, dy1), QPointF(dx2, dy2));
}

void Robot::gaugeReaded(qreal gauge)
{
	qWarning() << "GaugeReaded" << gauge;
}
