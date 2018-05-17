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
	// �ۺ�����������ͼ�����˲�
	void filteImg();
signals:
	// ���������ź�
	void paramsChanged();
private:
	QButtonGroup * filterstyle_buttongroup;    // �˲������Ͱ�ť��
	QLabel *slider_value;                      // ��ʾ��ǰ�˴�С
	QSlider *pslider;                          // �˴�С�Ļ�����
};

