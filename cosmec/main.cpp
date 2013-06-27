#include "cosmec.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	cosmec w;
	w.show();
	return a.exec();
}
