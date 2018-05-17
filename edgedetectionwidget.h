#pragma once
#include <QWidget>
class QButtonGroup;
class QLabel;
class QSlider;

class EdgeDetectionWidget:public QWidget
{
	Q_OBJECT
public:
	EdgeDetectionWidget();
	~EdgeDetectionWidget();
	void edgeDetection();
signals:
	void paramsChanged();
private:
	QButtonGroup *operatortype_buttongroup;
	QButtonGroup *kernelsize_buttongroup;
	QButtonGroup *edgeorientation_buttongroup;
	QLabel *lowthreshold_value_label;
	QLabel *highl_low_ratio_label;
	QSlider *lowthreshold_slider;
	QSlider *highl_low_ratio_slider;
};

