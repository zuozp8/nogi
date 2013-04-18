#ifndef VISUALISER_HPP
#define VISUALISER_HPP

#include <QWidget>

namespace Ui {
	class Visualiser;
}

class Visualiser : public QWidget
{
	Q_OBJECT
	
public:
	explicit Visualiser(QWidget *parent = 0);
	~Visualiser();
	
private slots:
	void on_speedSlider_valueChanged(int value);

	void on_particlesAmountSlider_valueChanged(int value);

	void on_fogRadioButton_toggled(bool checked);

private:
	Ui::Visualiser *ui;
};

#endif // VISUALISER_HPP
