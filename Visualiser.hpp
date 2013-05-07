#ifndef VISUALISER_HPP
#define VISUALISER_HPP

#include <QWidget>
#include "World.hpp"
#include "ui_Visualiser.h"
#include "Robot.hpp"
#include "ParticleFilter.hpp"

#define VISUALISER (Visualiser::getInstance())

namespace Ui {
	class Visualiser;
}

class Visualiser : public QWidget
{
	Q_OBJECT
	
public:
	static Visualiser* getInstance();
	~Visualiser();

	Ui::Visualiser *ui;

	int particlesAmount() const;
	QVector<ParticleFilter::Particle> getParticles();
protected:
	void timerEvent(QTimerEvent *);
	
private slots:
	void on_speedSlider_valueChanged(int value);
	void on_particlesAmountSlider_valueChanged();

	void on_fogRadioButton_toggled(bool checked);

	void on_aboutButton_clicked();

	void on_clearFogs_clicked();

	void on_stepButton_clicked();

	void on_resetButton_clicked();

private:
	explicit Visualiser();
	int timerId;
	Robot* robot;
	ParticleFilter* particleFilter;
};

#endif // VISUALISER_HPP
