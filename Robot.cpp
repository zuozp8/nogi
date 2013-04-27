#include "Robot.hpp"
#include "Visualiser.hpp"
#include <QDebug>

Robot::Robot(QObject *parent) :
	QObject(parent)
{
}

void Robot::step()
{
	int val1 = VISUALISER->ui->direction1->value();
	int val2 = VISUALISER->ui->direction2->value();

	int min = VISUALISER->ui->direction1->minimum();
	int max = VISUALISER->ui->direction1->maximum();


	qreal pi = 3.1415;

	qreal alfa1 = pi*qreal(val1)/(max-min);
	qreal alfa2 = pi*qreal(val2)/(max-min);

	qreal dx1 = -cos(alfa1);
	qreal dy1 = -sin(alfa1);

	qreal dx2 = -cos(alfa2);
	qreal dy2 = -sin(alfa2);

	emit moves(QPointF(dx1, dy1), QPointF(dx2, dy2));

	//emit moves(QPointF(0., 1.), QPointF(0., 1.));
}

void Robot::gaugeReaded(qreal gauge)
{
	qWarning() << "GaugeReaded" << gauge;
}
