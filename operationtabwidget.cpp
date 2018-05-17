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
	// �˲�
	filterwidget = new FilterWidget;
	connect(filterwidget, &FilterWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// ��̬ѧ����
	morphologytransformwidget = new MorphologyTransformWidget;
	connect(morphologytransformwidget, &MorphologyTransformWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// ��ֵ����
	thresholdwidget = new ThresholdWidget;
	connect(thresholdwidget, &ThresholdWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// ��Ե���
	edgedectionwidget = new EdgeDetectionWidget;
	connect(edgedectionwidget, &EdgeDetectionWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// ����任
	houghtransformwidget = new HoughTransformWidget;
	connect(houghtransformwidget, &HoughTransformWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);
	// ��������
	otherswidget = new OthersWidget;
	connect(otherswidget, &OthersWidget::paramsChanged, this, &OperationTabWidget::paramsChanged);

	tabwidget->addTab(filterwidget, QString::fromLocal8Bit("�����˲�"));
	tabwidget->addTab(morphologytransformwidget, QString::fromLocal8Bit("��̬ѧ�任"));
	tabwidget->addTab(thresholdwidget, QString::fromLocal8Bit("������ֵ����"));
	tabwidget->addTab(edgedectionwidget, QString::fromLocal8Bit("��Ե���"));
	tabwidget->addTab(houghtransformwidget, QString::fromLocal8Bit("����任"));
	tabwidget->addTab(otherswidget, QString::fromLocal8Bit("��������"));
	QGridLayout *main_layout = new QGridLayout;
	main_layout->addWidget(tabwidget);
	setLayout(main_layout);
}


OperationTabWidget::~OperationTabWidget()
{
}
