#include "houghtransformwidget.h"
#include "globalvar.h"
#include <QtWidgets>

using namespace cv;
using namespace std;

HoughTransformWidget::HoughTransformWidget()
{
	QGridLayout *main_layout = new QGridLayout;
	// 标准霍夫线变换
	QGroupBox *norm_hough_box = new QGroupBox(QString::fromLocal8Bit("标准霍夫线变换"));
	norm_hough_box->setFixedWidth(500);
	QHBoxLayout *norm_min_votes_layout = new QHBoxLayout;
	norm_min_votes_quantity_slider = new QSlider;
	norm_min_votes_quantity_slider->setOrientation(Qt::Horizontal);
	norm_min_votes_quantity_slider->setMinimum(20);
	norm_min_votes_quantity_slider->setMaximum(300);
	norm_min_votes_quantity_slider->setSliderPosition(300);
	norm_min_votes_quantity_slider->setTickPosition(QSlider::TicksBelow);
	connect(norm_min_votes_quantity_slider, &QSlider::valueChanged, this, &HoughTransformWidget::normHoughLinesTransform);
	norm_min_votes_value = new QLabel(QString::fromLocal8Bit("最少投票数:300"));
	norm_min_votes_layout->addWidget(norm_min_votes_value);
	norm_min_votes_layout->addWidget(norm_min_votes_quantity_slider);
	norm_hough_box->setLayout(norm_min_votes_layout);

	//统计概率霍夫线变换
	QGroupBox *prob_hough_box = new QGroupBox(QString::fromLocal8Bit("统计概率霍夫线变换"));
	prob_hough_box->setFixedWidth(500);
	QVBoxLayout *prob_hough_box_layout = new QVBoxLayout;
	QHBoxLayout *prob_min_votes_layout = new QHBoxLayout;
	prob_min_votes_quantity_slider = new QSlider;
	prob_min_votes_quantity_slider->setOrientation(Qt::Horizontal);
	prob_min_votes_quantity_slider->setMinimum(20);
	prob_min_votes_quantity_slider->setMaximum(300);
	prob_min_votes_quantity_slider->setSliderPosition(300);
	prob_min_votes_quantity_slider->setTickPosition(QSlider::TicksBelow);
	connect(prob_min_votes_quantity_slider, &QSlider::valueChanged, this, &HoughTransformWidget::probHoughLinesTransform);
	prob_min_votes_value = new QLabel(QString::fromLocal8Bit("最少投票数:300"));
	prob_min_votes_layout->addWidget(prob_min_votes_value);
	prob_min_votes_layout->addWidget(prob_min_votes_quantity_slider);

	QHBoxLayout *min_compose_quantity_layout = new QHBoxLayout;
	min_compose_quantity_slider = new QSlider;
	min_compose_quantity_slider->setOrientation(Qt::Horizontal);
	min_compose_quantity_slider->setMinimum(10);
	min_compose_quantity_slider->setMaximum(200);
	min_compose_quantity_slider->setTickPosition(QSlider::TicksBelow);
	connect(min_compose_quantity_slider, &QSlider::valueChanged, this, &HoughTransformWidget::probHoughLinesTransform);
	min_compose_quantity_label = new QLabel(QString::fromLocal8Bit("最少构成点数量:20"));
	min_compose_quantity_layout->addWidget(min_compose_quantity_label);
	min_compose_quantity_layout->addWidget(min_compose_quantity_slider);

	QHBoxLayout *max_gap_layout = new QHBoxLayout;
	max_gap_slider = new QSlider;
	max_gap_slider->setOrientation(Qt::Horizontal);
	max_gap_slider->setMinimum(0);
	max_gap_slider->setMaximum(20);
	max_gap_slider->setTickPosition(QSlider::TicksBelow);
	connect(max_gap_slider, &QSlider::valueChanged, this, &HoughTransformWidget::probHoughLinesTransform);
	max_gap_label = new QLabel(QString::fromLocal8Bit("最大间隔距离:0"));
	max_gap_layout->addWidget(max_gap_label);
	max_gap_layout->addWidget(max_gap_slider);

	prob_hough_box_layout->addLayout(prob_min_votes_layout);
	prob_hough_box_layout->addLayout(min_compose_quantity_layout);
	prob_hough_box_layout->addLayout(max_gap_layout);

	prob_hough_box->setLayout(prob_hough_box_layout);

	main_layout->addWidget(norm_hough_box);
	main_layout->addWidget(prob_hough_box);

	setLayout(main_layout);

}

HoughTransformWidget::~HoughTransformWidget()
{
}

void HoughTransformWidget::normHoughLinesTransform()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			vector<Vec2f> lines;
			cvtColor(in_img, out_img, CV_GRAY2BGR);
			int norm_min_votes = norm_min_votes_quantity_slider->value();
			norm_min_votes_value->setText(QString::fromLocal8Bit("最少投票数:%1").arg(norm_min_votes));
			HoughLines(in_img, lines, 1, CV_PI / 180, norm_min_votes, 0, 0);
			for (size_t i = 0; i < lines.size(); i++)
			{
				float rho = lines[i][0], theta = lines[i][1];
				Point pt1, pt2;
				double a = cos(theta), b = sin(theta);
				double x0 = a * rho, y0 = b * rho;
				pt1.x = cvRound(x0 + 1000 * (-b));
				pt1.y = cvRound(y0 + 1000 * (a));
				pt2.x = cvRound(x0 - 1000 * (-b));
				pt2.y = cvRound(y0 - 1000 * (a));
				line(out_img, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
			}
			emit paramsChanged();
		}
		else
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，转个灰度吧！"), QMessageBox::Yes);
			return;
		}
		
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
		return;
	}
	
}

void HoughTransformWidget::probHoughLinesTransform()
{
	int prob_min_votes = prob_min_votes_quantity_slider->value();
	prob_min_votes_value->setText(QString::fromLocal8Bit("最少投票数:%1").arg(prob_min_votes));
	int min_compose_quantity = min_compose_quantity_slider->value();
	min_compose_quantity_label->setText(QString::fromLocal8Bit("最少构成点数量:%1").arg(min_compose_quantity));
	int max_gap = max_gap_slider->value();
	max_gap_label->setText(QString::fromLocal8Bit("最大间隔距离:%1").arg(max_gap));
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			vector<Vec4i> lines;
			cvtColor(in_img, out_img, CV_GRAY2BGR);
			HoughLinesP(in_img, lines, 1, CV_PI / 180, prob_min_votes, min_compose_quantity, max_gap);
			for (size_t i = 0; i < lines.size(); i++)
			{
				Vec4i l = lines[i];
				line(out_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
			}
			emit paramsChanged();
		}
		else
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，转个灰度吧！"), QMessageBox::Yes);
			return;
		}
		
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
		return;
	}
}
