#include "World.hpp"
#include <QDebug>

World::World(QObject *parent) :
	QObject(parent)
{
	leg1Position = QPointF(100, 300);
	leg2Position = QPointF(500, 200);
}

qreal World::biasedGaugeForRealLegs()
{
	return unbiasedGaugeForLegs(leg1Position, leg2Position);
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
	unbiasedGaugeForLegs(leg1Position, leg2Position);
	//test odleglosci
}

void World::robotMoves(QPointF vector, QPointF vector2)
{
	// Add bias
	leg1Position += vector;
	leg2Position += vector;
	qreal biasedGauge = biasedGaugeForRealLegs();
	emit robotGaugeReady(biasedGauge);
}

QVector<World::Fog> World::fogs()
{
	return fogArray;
}

bool World::isInInterval(qreal p, qreal a, qreal b){
	return (p <= a && p >= b) || (p >= a && p <= b);
}

bool World::isInFog(QPointF leg, Fog f){
	qreal r2 = f.r*f.r;
	qreal xf = qreal(f.position.x());
	qreal yf = qreal(f.position.y());
	qreal xl = qreal(leg.x());
	qreal yl = qreal(leg.y());

	qreal dist = pow(xf - xl, 2) + pow(yf - yl, 2);

	return dist <= r2;
}

qreal World::updateVisibility(qreal actual, qreal density){
	if(1.0 - density < actual){
		qWarning()<<1.0 - density;
		return 1.0 - density;
	}
	return actual;
}
qreal World::unbiasedGaugeForLegs(QPointF l1, QPointF l2)
{
	// wspolczynniki prostej przechodzacej przez obie nogi
	qreal A = l2.y() - l1.y();
	qreal B = l1.x() - l2.x();
	qreal C = -A*l1.x() - B*l1.y();

	qreal minVisibility = 1.0;

	foreach(Fog f, fogArray) {
		qreal xf = f.position.x();
		qreal yf = f.position.y();

		// czy ktorakolwiek noga jest we mgle
		if(isInFog(l1, f) || isInFog(l2,f)){
			minVisibility = updateVisibility(minVisibility, f.density);
		}else{
			// odleglosc srodka mgly od prostej
			qreal dist = qAbs(A*xf + B*yf + C)/qSqrt(A*A + B*B);

			if(dist < f.r){// jesli mniejsza niz promien mgly
				// wspolczynniki prostej prostopadlej to osi nog przechodzacej przez srodek mgly
				qreal Af = -B;
				qreal Bf = A;
				qreal Cf = -Af*f.position.x() - Bf*f.position.y();
				// punkt przeciecia obu prostych
				qreal yd = (Cf*A - C*Af)/(B*Af - Bf*A);
				qreal xd = (-C - B*yd)/A;
				// czy punkt zawiera sie pomiedzy nogami
				if(isInInterval(xd, l1.x(), l2.x()) && isInInterval(yd, l1.y(), l2.y())){
					minVisibility = updateVisibility(minVisibility, f.density);
				}else{
					qWarning() << "nie nachodzi";
				}
			}else{
				qWarning() << "nie nachodzi";
			}
		}
	}
	return minVisibility;
}

World *World::getInstance()
{
	static World* instance = new World();
	return instance;
}
