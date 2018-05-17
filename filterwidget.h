#pragma once
#include <QWidget>
#include <QString>
class QButtonGroup;
class QLabel;
class QSlider;

enum FilterStyle
{
	Blur,
	Gussian,
	Median,
	Bilateral
};

class FilterWidget :public QWidget
{
	Q_OBJECT
public:
	FilterWidget();
	~FilterWidget();
	// 槽函数：对输入图进行滤波
	void filteImg();
signals:
	// 参数调整信号
	void paramsChanged();
private:
	QButtonGroup * filterstyle_buttongroup;    // 滤波器类型按钮组
	QLabel *slider_value;                      // 显示当前核大小
	QSlider *pslider;                          // 核大小的滑动条
};

