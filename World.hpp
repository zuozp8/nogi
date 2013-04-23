#ifndef WORLD_HPP
#define WORLD_HPP

#include <QObject>
#include <QPoint>
#include <QPair>
#include <QVector>
#include <qmath.h>

#define WORLD (World::getInstance())

class World : public QObject
{
	Q_OBJECT

public:
	static World* getInstance();
	QPoint dimenstions();

	struct Fog{
		QPointF position;
		int r;
        qreal density;//<0,1>??
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
};

#endif // WORLD_HPP
