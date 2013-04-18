#include "Visualiser.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Visualiser w;
	w.show();
	
	return a.exec();
}
