#ifndef PARTICLEFILTER_HPP
#define PARTICLEFILTER_HPP

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPair>

class ParticleFilter : public QObject
{
	Q_OBJECT
public:

	struct Particle {
		QPointF leg1, leg2;
		qreal propability;
	};

	explicit ParticleFilter(QObject *parent = 0);
	
	QVector<Particle> getParticles();
	void clear();

signals:
	
public slots:
	void gaugeReaded(qreal gauge);
	void robotMoves(QPointF vector1, QPointF vector2);

private:
	void initializeParticles();
	std::default_random_engine generator;
	QVector<Particle> particles;
};

#endif // PARTICLEFILTER_H
