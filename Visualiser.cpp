#include "Visualiser.hpp"

#include <QDebug>
#include <QMessageBox>

Visualiser::Visualiser() :
	ui(new Ui::Visualiser)
{
	ui->setupUi(this);

	connect(WORLD, SIGNAL(robotGaugeReady(qreal)), ui->canvas, SLOT(setLastGauge(qreal)));

	robot = new Robot();
	connect(WORLD, SIGNAL(robotGaugeReady(qreal)), robot, SLOT(gaugeReaded(qreal)));
	connect(robot, SIGNAL(moves(QPointF,QPointF)), WORLD, SLOT(robotMoves(QPointF,QPointF)));

	QPalette *p = new QPalette();
	p->setColor(QPalette::Foreground, LEG1COLOR);
	ui->leg1RadioButton->setPalette(*p);

	p = new QPalette();
	p->setColor(QPalette::Foreground, LEG2COLOR);
	ui->leg2RadioButton->setPalette(*p);

	on_speedSlider_valueChanged(ui->speedSlider->value());
	on_particlesAmountSlider_valueChanged(ui->particlesAmountSlider->value());
	timerId = 0;
}

Visualiser::~Visualiser()
{
	delete ui;
}

void Visualiser::timerEvent(QTimerEvent *)
{
	robot->step();
	ui->canvas->update();
}

void Visualiser::on_speedSlider_valueChanged(int value)
{
	ui->speedValueLabel->setText(QString("%0 FPS").arg(value ? 1 << (value-1) : 0));
	ui->stepButton->setEnabled(value == 0);
	if (timerId>0) {
		killTimer(timerId);
		timerId = 0;
	}
	if (value) {
		timerId = startTimer(1000>>(value-1));
	}
}

void Visualiser::on_particlesAmountSlider_valueChanged(int value)
{
	ui->particlesAmountValueLabel->setText(QString("%0").arg(200 * (1 << value)));
}

void Visualiser::on_fogRadioButton_toggled(bool checked)
{
	ui->fogDensityLabel->setEnabled(checked);
	ui->fogDensity->setEnabled(checked);
	ui->fogRadiusLabel->setEnabled(checked);
	ui->fogRadius->setEnabled(checked);
}

void Visualiser::on_controlDirections_toggled(bool checked)
{
	ui->direction1->setEnabled(checked);
	ui->direction2->setEnabled(checked);
}

void Visualiser::on_aboutButton_clicked()
{
	QMessageBox::information(this, "O programie",
													 "Foo foo tutaj coś napiszemy\n"
													 "Wykonanie: Konrad Baumgart i Kalina Jasinska");
}


Visualiser *Visualiser::getInstance()
{
	static Visualiser* instance = new Visualiser();
	return instance;
}

void Visualiser::on_clearFogs_clicked()
{
	WORLD->clearFogs();
	ui->canvas->update();
}

void Visualiser::on_stepButton_clicked()
{
	timerEvent(NULL);
}
