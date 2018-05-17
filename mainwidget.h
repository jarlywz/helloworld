#pragma once
#include <QWidget>
class OperationTabWidget;
class InOutImgWidget;

class MainWidget :public QWidget
{
	Q_OBJECT
public:
	MainWidget();
	~MainWidget();
private:
	OperationTabWidget * operationtabwidget;
	InOutImgWidget *inoutimgwidget;
};

