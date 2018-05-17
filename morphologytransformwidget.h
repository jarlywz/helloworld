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
	// ��ͼ�������̬ѧ�任
	void morphologyTransformImg();
signals:
	// ���������ź�
	void paramsChanged();
private:
	QButtonGroup * mophologystyle_buttongroup;    // ��̬ѧ�������Ͱ�ť��
	QButtonGroup * elementstyle_buttongroup;      // �ں����Ͱ�ť��
	QLabel *slider_value;                         // ��ʾ��ǰ�˴�С
	QSlider *pslider;                             // �˴�С�Ļ�����
};

