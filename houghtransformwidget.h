#pragma once
#include <QWidget>
class QLabel;
class QSlider;

class HoughTransformWidget:public QWidget
{
	Q_OBJECT
public:
	HoughTransformWidget();
	~HoughTransformWidget();
	void normHoughLinesTransform();
	void probHoughLinesTransform();
signals:
	void paramsChanged();
private:
	QLabel * norm_min_votes_value;
	QSlider * norm_min_votes_quantity_slider;
	QLabel *prob_min_votes_value;
	QSlider * prob_min_votes_quantity_slider;
	QLabel *min_compose_quantity_label;
	QSlider *min_compose_quantity_slider;
	QLabel *max_gap_label;
	QSlider *max_gap_slider;
};

