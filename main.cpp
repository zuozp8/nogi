#include "Visualiser.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings((QTextCodec::codecForName("UTF-8")));
	Visualiser* v = VISUALISER;
	v->show();
	
	return a.exec();
}
