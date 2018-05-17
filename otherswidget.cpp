#include "otherswidget.h"
#include "globalvar.h"
#include <QtWidgets>

using namespace cv;
using namespace std;

OthersWidget::OthersWidget()
{
	QGridLayout *main_layout = new QGridLayout;
	equalizeHist_button = new QPushButton(QString::fromLocal8Bit("直方图均衡化"));
	connect(equalizeHist_button, &QPushButton::clicked, this, &OthersWidget::m_equalizeHist);

	findcontours_button = new QPushButton(QString::fromLocal8Bit("寻找轮廓"));
	connect(findcontours_button, &QPushButton::clicked, this, &OthersWidget::m_findcontours);

	QGroupBox *partequalizebox = new QGroupBox;
	QVBoxLayout *partequalize_layout = new QVBoxLayout;
	cliplimt_slider = new QSlider;
	cliplimt_slider->setMinimum(0);
	cliplimt_slider->setMaximum(60);
	cliplimt_slider->setTickPosition(QSlider::TicksBelow);
	cliplimt_slider->setOrientation(Qt::Horizontal);
	connect(cliplimt_slider, &QSlider::valueChanged, this, &OthersWidget::partEqualize);
	tilegridsize_slider = new QSlider;
	tilegridsize_slider->setMinimum(1);
	tilegridsize_slider->setMaximum(20);
	tilegridsize_slider->setTickPosition(QSlider::TicksBelow);
	tilegridsize_slider->setOrientation(Qt::Horizontal);
	connect(tilegridsize_slider, &QSlider::valueChanged, this, &OthersWidget::partEqualize);
	partequalize_layout->addWidget(cliplimt_slider);
	partequalize_layout->addWidget(tilegridsize_slider);
	partequalizebox->setLayout(partequalize_layout);

	main_layout->addWidget(equalizeHist_button, 0, 0, 1, 1);
	main_layout->addWidget(findcontours_button, 0, 1, 1, 1);
	main_layout->addWidget(partequalizebox, 1, 0, 1, 2);


	setLayout(main_layout);
}


OthersWidget::~OthersWidget()
{
}

void OthersWidget::m_equalizeHist()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			equalizeHist(in_img, out_img);
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

void OthersWidget::m_findcontours()
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	out_img.create(in_img.size(), CV_8UC3);
	findContours(in_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//for (int i = 0; i< contours.size(); i++)
	//{
	//	drawContours(out_img, contours, i, (0,0,255), 2, 8, hierarchy, 0, Point());
	//}
	qDebug() << contours.size();
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<RotatedRect> minRect(contours.size());
	Mat temp = out_img;
	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}
	for (int i = 0; i< contours.size(); i++)
	{
		
		drawContours(out_img, contours_poly, i, Scalar(0, 0, 0), 1, 8, vector<Vec4i>(), 0, Point());
		//rectangle(out_img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2, 8, 0);
		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(out_img, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 1, 8);
	}
	emit paramsChanged();
}

void OthersWidget::partEqualize()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			double cliplimt = cliplimt_slider->value();
			int tilegridsize = tilegridsize_slider->value();
			Ptr<CLAHE> clahe = createCLAHE(cliplimt, Size(tilegridsize, tilegridsize));
			clahe->apply(in_img, out_img);
			emit paramsChanged();
		}
	}
}
