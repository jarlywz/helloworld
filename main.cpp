#include "mainwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	w.setWindowTitle(QString::fromLocal8Bit("����С����"));
	w.show();
	return a.exec();
}