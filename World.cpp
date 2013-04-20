#include "World.hpp"

World::World(QObject *parent) :
	QObject(parent)
{
	leg1Position = QPointF(100, 300);
	leg2Position = QPointF(500, 200);
}

QPoint World::dimenstions()
{
	return QPoint(600, 400);
}

QPair<QPointF, QPointF> World::robotPosition()
{
	return qMakePair(leg1Position, leg2Position);
}

void World::setLeg1Posision(QPointF pos)
{
	leg1Position = pos;
}

void World::setLeg2Posision(QPointF pos)
{
	leg2Position = pos;
}

void World::clearFogs()
{
	fogArray.clear();
}

void World::addFog(Fog f)
{
	fogArray.append(f);
}

void World::robotMoves(QPointF vector, QPointF vector2)
{
	//Add bias
}


QVector<World::Fog> World::fogs()
{
	return fogArray;
}

qreal World::unbiasedGaugeForLegs(QPointF l1, QPointF l2)
{
	return 1.;
}


World *World::getInstance()
{
	static World* instance = new World();
	return instance;
}
