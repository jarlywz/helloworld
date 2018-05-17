#pragma once
#include <QWidget>
class QButtonGroup;
class QLabel;
class QSlider;

class ThresholdWidget:public QWidget
{
	Q_OBJECT
public:
	ThresholdWidget();
	~ThresholdWidget();
	void threshImg();
signals:
	void paramsChanged();
private:
	QButtonGroup *threshtype_buttongroup;         // 形态学操作类型按钮组
	QLabel *slider_value;                         // 显示当前核大小
	QSlider *pslider;                             // 核大小的滑动条
};

