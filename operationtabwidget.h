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
	// 参数调整信号
	void paramsChanged();
private:
	// 滤波
	FilterWidget *filterwidget;
	// 形态学变化
	MorphologyTransformWidget *morphologytransformwidget;
	// 阈值操作
	ThresholdWidget *thresholdwidget;
	// 边缘检测
	EdgeDetectionWidget *edgedectionwidget;
	// 霍夫变换
	HoughTransformWidget *houghtransformwidget;
	// 其它操作
	OthersWidget *otherswidget;
};

