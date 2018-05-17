#include "edgedetectionwidget.h"
#include "globalvar.h"
#include <QtWidgets>

using namespace cv;

EdgeDetectionWidget::EdgeDetectionWidget()
{
	QGridLayout *main_layout = new QGridLayout;
	// 算子类型选项
	QGroupBox *operatortype_button_box = new QGroupBox(QString::fromLocal8Bit("算子类型"));
	QHBoxLayout *operatortype_button_layout = new QHBoxLayout;
	operatortype_buttongroup = new QButtonGroup;
	connect(operatortype_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, &EdgeDetectionWidget::edgeDetection);
	QStringList operatorlist;
	operatorlist << "Sobel" << "Scharr" << "Laplace" << "Canny";
	for (int i = 0; i < 4; i++)
	{
		QRadioButton *pbutton = new QRadioButton(operatorlist.at(i));
		operatortype_buttongroup->setId(pbutton, i);
		if (i == 0)
		{
			pbutton->setChecked(true);
		}
		operatortype_buttongroup->addButton(pbutton);
		operatortype_button_layout->addWidget(pbutton);
	}
	operatortype_button_box->setLayout(operatortype_button_layout);

	// 内核大小选项
	QGroupBox *kernelsize_button_box = new QGroupBox(QString::fromLocal8Bit("内核大小"));
	QVBoxLayout *kernelsize_button_layout = new QVBoxLayout;
	kernelsize_buttongroup = new QButtonGroup;
	connect(kernelsize_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, &EdgeDetectionWidget::edgeDetection);
	QStringList kernelsizelist;
	kernelsizelist << "1" << "3" << "5" << "7";
	for (int i = 0; i < 4; i++)
	{
		QRadioButton *pbutton = new QRadioButton(kernelsizelist.at(i));
		kernelsize_buttongroup->setId(pbutton, i);
		if (i == 1)
		{
			pbutton->setChecked(true);
		}
		kernelsize_buttongroup->addButton(pbutton);
		kernelsize_button_layout->addWidget(pbutton);
	}
	kernelsize_button_box->setLayout(kernelsize_button_layout);

	// 边缘检测方向
	QGroupBox *edgeorientation_button_box = new QGroupBox(QString::fromLocal8Bit("边缘检测方向"));
	QVBoxLayout *edgeorientation_button_layout = new QVBoxLayout;
	edgeorientation_buttongroup = new QButtonGroup;
	connect(edgeorientation_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, &EdgeDetectionWidget::edgeDetection);
	QStringList edgeorientationlist;
	edgeorientationlist << "X" << "Y" << "X and Y";
	for (int i = 0; i < 3; i++)
	{
		QRadioButton *pbutton = new QRadioButton(edgeorientationlist.at(i));
		edgeorientation_buttongroup->setId(pbutton, i);
		if (i == 2)
		{
			pbutton->setChecked(true);
		}
		edgeorientation_buttongroup->addButton(pbutton);
		edgeorientation_button_layout->addWidget(pbutton);
	}
	edgeorientation_button_box->setLayout(edgeorientation_button_layout);

	// 最低阈值滑动条
	QGroupBox *lowthreshold_slider_box = new QGroupBox(QString::fromLocal8Bit("最低阈值"));
	QHBoxLayout *lowthreshold_slider_layout = new QHBoxLayout;
	lowthreshold_slider = new QSlider;
	lowthreshold_slider->setOrientation(Qt::Horizontal);
	lowthreshold_slider->setMinimum(0);
	lowthreshold_slider->setMaximum(100);
	lowthreshold_slider->setTickPosition(QSlider::TicksBelow);
	connect(lowthreshold_slider, &QSlider::valueChanged, this, &EdgeDetectionWidget::edgeDetection);
	lowthreshold_value_label = new QLabel(QString::fromLocal8Bit("最低阈值:0"));
	lowthreshold_slider_layout->addWidget(lowthreshold_value_label);
	lowthreshold_slider_layout->addWidget(lowthreshold_slider);
	lowthreshold_slider_box->setLayout(lowthreshold_slider_layout);

	// 高低阈值比滑动条
	QGroupBox *highl_low_ratio_box = new QGroupBox(QString::fromLocal8Bit("高低阈值比"));
	QHBoxLayout *highl_low_ratio_slider_layout = new QHBoxLayout;
	highl_low_ratio_slider = new QSlider;
	highl_low_ratio_slider->setOrientation(Qt::Horizontal);
	highl_low_ratio_slider->setMinimum(10);
	highl_low_ratio_slider->setMaximum(30);
	highl_low_ratio_slider->setTickPosition(QSlider::TicksBelow);
	highl_low_ratio_slider->setSliderPosition(30);
	connect(highl_low_ratio_slider, &QSlider::valueChanged, this, &EdgeDetectionWidget::edgeDetection);
	highl_low_ratio_label = new QLabel(QString::fromLocal8Bit("高低阈值比:3.0"));
	highl_low_ratio_slider_layout->addWidget(highl_low_ratio_label);
	highl_low_ratio_slider_layout->addWidget(highl_low_ratio_slider);
	highl_low_ratio_box->setLayout(highl_low_ratio_slider_layout);

	// 执行按钮
	QPushButton *carryout_button = new QPushButton(QString::fromLocal8Bit("边缘检测"));
	connect(carryout_button, &QPushButton::clicked, this, &EdgeDetectionWidget::edgeDetection);
	main_layout->addWidget(operatortype_button_box, 0, 0, 1, 3);
	main_layout->addWidget(kernelsize_button_box, 1, 0, 3, 1);
	main_layout->addWidget(edgeorientation_button_box, 1, 1, 3, 1);
	main_layout->addWidget(lowthreshold_slider_box, 1, 2, 1, 1);
	main_layout->addWidget(highl_low_ratio_box, 2, 2, 1, 1);
	main_layout->addWidget(carryout_button, 3, 2, 1, 1);
	
	setLayout(main_layout);
}


EdgeDetectionWidget::~EdgeDetectionWidget()
{
}

void EdgeDetectionWidget::edgeDetection()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
			int orientation_id = edgeorientation_buttongroup->checkedId();
			int operator_type_id = operatortype_buttongroup->checkedId();
			int kernel_size = -(kernelsize_buttongroup->checkedId()) * 2 - 1;
			double min_threshold_value = lowthreshold_slider->value();
			lowthreshold_value_label->setText(QString::fromLocal8Bit("最低阈值:%1").arg(min_threshold_value));
			double max_min_ratio = double(highl_low_ratio_slider->value()) / 10;
			highl_low_ratio_label->setText(QString::fromLocal8Bit("高低阈值比:%1").arg(QString::number(max_min_ratio,'f',1)));
			switch (operator_type_id)
			{
			case -1:
				switch (orientation_id)
				{
				case -1:
					Sobel(in_img, out_img, -1, 1, 0, kernel_size, 1, 0, BORDER_DEFAULT);
					emit paramsChanged();
					break;
				case -2:
					Sobel(in_img, out_img, -1, 0, 1, kernel_size, 1, 0, BORDER_DEFAULT);
					emit paramsChanged();
					break;
				case -3:
					Sobel(in_img, grad_x, -1, 1, 0, kernel_size, 1, 0, BORDER_DEFAULT);
					Sobel(in_img, grad_y, -1, 0, 1, kernel_size, 1, 0, BORDER_DEFAULT);
					/*convertScaleAbs(grad_x, abs_grad_x);
					convertScaleAbs(grad_y, abs_grad_y);*/
					addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out_img);
					emit paramsChanged();
					break;
				default:
					break;
				}
				break;
			case -2:
				switch (orientation_id)
				{
				case -1:
					Scharr(in_img, out_img, -1, 1, 0, kernel_size, 1, 0);
					emit paramsChanged();
					break;
				case -2:
					Scharr(in_img, out_img, -1, 0, 1, kernel_size, 1, 0);
					emit paramsChanged();
					break;
				case -3:
					Scharr(in_img, grad_x, -1, 1, 0, kernel_size, 1, 0);
					Scharr(in_img, grad_y, -1, 0, 1, kernel_size, 1, 0);
					convertScaleAbs(grad_x, abs_grad_x);
					convertScaleAbs(grad_y, abs_grad_y);
					addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out_img);
					emit paramsChanged();
					break;
				default:
					break;
				}
				break;
			case -3:
				Laplacian(in_img, out_img, -1, kernel_size, 1, 0, BORDER_DEFAULT);
				emit paramsChanged();
				break;
			case -4:
				if (kernel_size == 1)
				{
					QMessageBox::warning(this, "warning", QString::fromLocal8Bit("骚瑞，老哥！canny算子内核不能为1"), QMessageBox::Yes);
					break;
				}
				else
				{
					Canny(in_img, out_img, min_threshold_value, min_threshold_value*max_min_ratio, kernel_size);
					emit paramsChanged();
					break;
				}
			default:
				break;
			}
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
