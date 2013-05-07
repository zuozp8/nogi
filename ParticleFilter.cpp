#include "ParticleFilter.hpp"
#include "World.hpp"
#include "Visualiser.hpp"
#include <QSlider>
#include <qmath.h>
#include <QDebug>

ParticleFilter::ParticleFilter(QObject *parent) :
	QObject(parent)
{
}

QVector<ParticleFilter::Particle> ParticleFilter::getParticles()
{
	if (particles.empty())
		initializeParticles();
	return particles;
}

void ParticleFilter::clear()
{
	particles.clear();
}

void ParticleFilter::gaugeReaded(qreal gauge) {
	qreal maxPropability = 0.;
	for (int i=0; i<particles.size(); i++) {
		Particle& p = particles[i];
		qreal particleGauge = WORLD->unbiasedGaugeForLegs(p.leg1, p.leg2);

		//Testing if gauge == particleGauge
		qreal difference = gauge - particleGauge;
		p.propability = (p.propability + 0.1)/1.1;
		p.propability *= qExp(-(difference*difference)/(2*WORLD->getDistributionForGauge().stddev()));

		maxPropability = qMax(maxPropability, p.propability);
	}

	//normalizing
	for (int i=0; i<particles.size(); i++) {
		particles[i].propability /= maxPropability;
	}
}

void ParticleFilter::robotMoves(QPointF vector1, QPointF vector2)
{
	QVector<Particle> oldParticles = particles;
	particles.clear();

	qreal maxPropability = 0.;
	foreach (Particle p, oldParticles) {
		maxPropability = qMax(maxPropability, p.propability);
	}
	std::uniform_real_distribution<qreal> distribution(0., 2*maxPropability);

	qreal b = 0;
	int index = qrand()%oldParticles.size();

	int particlesToCreate = VISUALISER->particlesAmount() * 0.998;

	for (int i = 0; i<particlesToCreate; i++) {
		b += distribution(generator);
		while (oldParticles[index].propability < b) {
			b -= oldParticles[index].propability;
			index = (index + 1) % oldParticles.size();
		}
		particles.append(oldParticles[index]);
	}

	//GENERATE RANDOM PARTICLES
	initializeParticles();

	for (int i=0; i<particles.size(); i++) {
		Particle& p = particles[i];
		p.leg1 += vector1 + 2.5*WORLD->getGlideBiasVector();
		p.leg2 += vector2 + 2.5*WORLD->getGlideBiasVector();
		WORLD->assureLegInField(p.leg1);
		WORLD->assureLegInField(p.leg2);
	}
}

void ParticleFilter::initializeParticles()
{
	std::uniform_real_distribution<qreal> distributionX(0., WORLD->dimenstions().x());
	std::uniform_real_distribution<qreal> distributionY(0., WORLD->dimenstions().y());

	while (particles.size() < VISUALISER->particlesAmount()) {
		particles.append({
											 QPointF(distributionX(generator), distributionY(generator)),
											 QPointF(distributionX(generator), distributionY(generator)),
											 .7});
	}
}
