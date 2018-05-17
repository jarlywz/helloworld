#pragma once
#include <QWidget>
class QPushButton;
class QSlider;

class OthersWidget:public QWidget
{
	Q_OBJECT
public:
	OthersWidget();
	~OthersWidget();
	void m_equalizeHist();
	void m_findcontours();
	void partEqualize();
signals:
	void paramsChanged();
private:
	QPushButton *equalizeHist_button;
	QPushButton *findcontours_button;
	QPushButton *partequalize_button;
	QSlider *cliplimt_slider;
	QSlider *tilegridsize_slider;
};