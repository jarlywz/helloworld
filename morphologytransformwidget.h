#pragma once
#include <QWidget>
class QButtonGroup;
class QLabel;
class QSlider;

class MorphologyTransformWidget:public QWidget
{
	Q_OBJECT
public:
	MorphologyTransformWidget();
	~MorphologyTransformWidget();
	// 对图像进行形态学变换
	void morphologyTransformImg();
signals:
	// 参数调整信号
	void paramsChanged();
private:
	QButtonGroup * mophologystyle_buttongroup;    // 形态学操作类型按钮组
	QButtonGroup * elementstyle_buttongroup;      // 内核类型按钮组
	QLabel *slider_value;                         // 显示当前核大小
	QSlider *pslider;                             // 核大小的滑动条
};

