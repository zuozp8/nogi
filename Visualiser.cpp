#include "Visualiser.hpp"
#include "ui_Visualiser.h"

#include <QDebug>

Visualiser::Visualiser(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Visualiser)
{
	ui->setupUi(this);

	on_speedSlider_valueChanged(ui->speedSlider->value());
	on_particlesAmountSlider_valueChanged(ui->particlesAmountSlider->value());
}

Visualiser::~Visualiser()
{
	delete ui;
}

void Visualiser::on_speedSlider_valueChanged(int value)
{
	ui->speedValueLabel->setText(QString("%0 FPS").arg(value ? 1 << (value-1) : 0));
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
