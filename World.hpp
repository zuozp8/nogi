#ifndef WORLD_HPP
#define WORLD_HPP

#include <QObject>
#include <QPoint>
#include <QPair>
#include <QVector>
#include <qmath.h>
#include <random>

#define WORLD (World::getInstance())


class World : public QObject
{
	Q_OBJECT

public:
	static World* getInstance();
	QPointF dimenstions();

	struct Fog{
		QPointF position;
		int r;
		qreal density;//[0,1]
	};
	QVector<Fog> fogs();

	QPair<QPointF, QPointF> robotPosition();
	void setLeg1Posision(QPointF);
	void setLeg2Posision(QPointF);

	qreal unbiasedGaugeForLegs(QPointF l1, QPointF l2);
signals:
	void robotGaugeReady(qreal);
	
public slots:
	void clearFogs();
	void addFog(Fog f);
	void robotMoves(QPointF vector1, QPointF vector2);

private:
	explicit World(QObject *parent = 0);

	QPointF leg1Position;
	QPointF leg2Position;
	QVector<Fog> fogArray;

	qreal biasedGaugeForRealLegs();

	qreal findFittingPosition(qreal max, qreal pos, qreal delta);
	void assureLegsInField();

	bool isInFog(QPointF leg, Fog f);
	bool isInInterval(qreal p, qreal a, qreal b);
	qreal updateVisibility(qreal actual, qreal density);

	std::default_random_engine generator;
	std::normal_distribution<qreal> distributionForMoves;
	std::normal_distribution<qreal> distributionForGauge;
};

#endif // WORLD_HPP
