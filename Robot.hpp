#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <QObject>
#include <QPointF>

class Robot : public QObject
{
	Q_OBJECT
public:
	explicit Robot(QObject *parent = 0);
	void step();
	
signals:
	void moves(QPointF vector1, QPointF vector2);

public slots:
	void gaugeReaded(qreal);
};

#endif // ROBOT_HPP
