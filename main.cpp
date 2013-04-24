#include "Visualiser.hpp"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	#if QT_VERSION < 0x050000
	QTextCodec::setCodecForCStrings((QTextCodec::codecForName("UTF-8")));
	#endif
	Visualiser* v = VISUALISER;
	v->show();
	
	return a.exec();
}
