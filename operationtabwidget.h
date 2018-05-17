#pragma once
#include <QWidget>
class FilterWidget;
class MorphologyTransformWidget;
class ThresholdWidget;
class EdgeDetectionWidget;
class HoughTransformWidget;
class OthersWidget;


class OperationTabWidget :public QWidget
{
	Q_OBJECT
public:
	OperationTabWidget();
	~OperationTabWidget();
signals:
	// ���������ź�
	void paramsChanged();
private:
	// �˲�
	FilterWidget *filterwidget;
	// ��̬ѧ�仯
	MorphologyTransformWidget *morphologytransformwidget;
	// ��ֵ����
	ThresholdWidget *thresholdwidget;
	// ��Ե���
	EdgeDetectionWidget *edgedectionwidget;
	// ����任
	HoughTransformWidget *houghtransformwidget;
	// ��������
	OthersWidget *otherswidget;
};

