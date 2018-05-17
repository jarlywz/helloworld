#include "mainwidget.h"
#include "operationtabwidget.h"
#include "inoutimgwidget.h"
#include <QtWidgets>


MainWidget::MainWidget()
{
	QGridLayout *main_layout = new QGridLayout();
	operationtabwidget = new OperationTabWidget;
	inoutimgwidget = new InOutImgWidget;
	connect(operationtabwidget, &OperationTabWidget::paramsChanged, inoutimgwidget, &InOutImgWidget::updateOutImg);
	main_layout->addWidget(operationtabwidget, 0, 0, 1, 1);
	main_layout->addWidget(inoutimgwidget, 0, 1, 1, 1);
	setLayout(main_layout);
}

MainWidget::~MainWidget()
{
}