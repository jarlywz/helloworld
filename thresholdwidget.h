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
	QButtonGroup *threshtype_buttongroup;         // ��̬ѧ�������Ͱ�ť��
	QLabel *slider_value;                         // ��ʾ��ǰ�˴�С
	QSlider *pslider;                             // �˴�С�Ļ�����
};

