#include "mainwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWidget w;
	w.setWindowTitle(QString::fromLocal8Bit("调参小工具"));
	w.show();
	return a.exec();
}