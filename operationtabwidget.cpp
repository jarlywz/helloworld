#include "operationtabwidget.h"
#include "filterwidget.h"
#include "morphologytransformwidget.h"
#include "thresholdwidget.h"
#include "edgedetectionwidget.h"
#include "houghtransformwidget.h"
#include "otherswidget.h"
#include <QtWidgets>

OperationTabWidget::OperationTabWidget()
{
	QTabWidget *tabwidget = new QTabWidget;
	// 滤波
	filterwidget = new FilterWidget;
	connect(filterwidget, &FilterWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// 形态学操作
	morphologytransformwidget = new MorphologyTransformWidget;
	connect(morphologytransformwidget, &MorphologyTransformWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// 阈值操作
	thresholdwidget = new ThresholdWidget;
	connect(thresholdwidget, &ThresholdWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// 边缘检测
	edgedectionwidget = new EdgeDetectionWidget;
	connect(edgedectionwidget, &EdgeDetectionWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// 霍夫变换
	houghtransformwidget = new HoughTransformWidget;
	connect(houghtransformwidget, &HoughTransformWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// 其它操作
	otherswidget = new OthersWidget;
	connect(otherswidget, &OthersWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);

	tabwidget->addTab(filterwidget, QString::fromLocal8Bit("基本滤波"));
	tabwidget->addTab(morphologytransformwidget, QString::fromLocal8Bit("形态学变换"));
	tabwidget->addTab(thresholdwidget, QString::fromLocal8Bit("基本阈值操作"));
	tabwidget->addTab(edgedectionwidget, QString::fromLocal8Bit("边缘检测"));
	tabwidget->addTab(houghtransformwidget, QString::fromLocal8Bit("霍夫变换"));
	tabwidget->addTab(otherswidget, QString::fromLocal8Bit("其它操作"));
	QGridLayout *main_layout = new QGridLayout;
	main_layout->addWidget(tabwidget);
	setLayout(main_layout);
}


OperationTabWidget::~OperationTabWidget()
{
}
