#ifndef VISUALISERCANVAS_HPP
#define VISUALISERCANVAS_HPP

#include <QWidget>

class VisualiserCanvas : public QWidget
{
	Q_OBJECT
public:
	explicit VisualiserCanvas(QWidget *parent = 0);

	int heightForWidth(int w) const;

protected:
	void paintEvent(QPaintEvent *);
signals:
	
public slots:
	
};

#endif // VISUALISERCANVAS_HPP
