#include "Robot.hpp"
#include <QDebug>

Robot::Robot(QObject *parent) :
	QObject(parent)
{
}

void Robot::step()
{
	//TODO
	emit moves(QPointF(0., 1.), QPointF(0., 1.));
}

void Robot::gaugeReaded(qreal gauge)
{
	qWarning() << "GaugeReaded" << gauge;
}
