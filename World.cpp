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
	unbiasedGaugeForLegs(leg1Position, leg2Position);
	//test odleglosci
}

void World::robotMoves(QPointF vector, QPointF vector2)
{   //robotMoves - robot wywoła tę funkcję jak się ruszy
	//z 2 wektorami
	//oznaczającymi co robi
	//a świat musi go poślizgnąć
	//Add bias
}


QVector<World::Fog> World::fogs()
{
	return fogArray;
}


bool isInInterval(qreal p, qreal a, qreal b){
	if((p <= a && p >= b) || (p >= a && p <= b)){
		return 1;
	}
	return 0;
}
qreal World::unbiasedGaugeForLegs(QPointF l1, QPointF l2)
{
	printf("UnbiasedGauge Begin\n");
	// wspolczynniki prostej przechodzacej przez obie nogi
	qreal A = l2.y() - l1.y();
	qreal B = l1.x() - l2.x();
	qreal C = -A*l1.x() - B*l1.y();

	qreal minVisibility = 1.0;

	for(int i = 0; i<fogArray.count(); i++){
		Fog f = fogArray.at(i);
		qreal x = f.position.x();
		qreal y = f.position.y();
		// odleglosc srodka mgly od prostej
		qreal dist = abs(A*x + B*y + C)/sqrt(A*A + B*B);

		if(dist < f.r){// jesli mniejsza niz promien mgly
			// wspolczynniki prostej prostopadlej to osi nog przechodzacej przez srodek mgly
			qreal Af = -B;
			qreal Bf = A;
			qreal Cf = -Af*f.position.x() - Bf*f.position.y();
			// punkt przeciecia obu prostych
			qreal yd = (Cf*A - C*Af)/(B*Af - Bf*A);//co z dzieleniem przez zero?
			qreal xd = (-C - B*yd)/A;
			// czy punkt zawiera sie pomiedzy nogami
			if(isInInterval(xd, l1.x(), l2.x()) && isInInterval(yd, l1.y(), l2.y())){
				if(1.0 - f.density < minVisibility)
					minVisibility = 1.0 - f.density;
				printf("%f\n", minVisibility);
			}else{
				printf("nie nachodzi\n");
			}
		}else{
			printf("nie nachodzi\n");
		}
	}
	return minVisibility;
}

World *World::getInstance()
{
	static World* instance = new World();
	return instance;
}
