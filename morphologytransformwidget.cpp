#include "morphologytransformwidget.h"
#include "globalvar.h"
#include <QtWidgets>

using namespace cv;

MorphologyTransformWidget::MorphologyTransformWidget()
{
	QGridLayout *main_layout = new QGridLayout;
	// ��̬ѧ��������
	QGroupBox *mophology_button_box = new QGroupBox(QString::fromLocal8Bit("��̬ѧ��������"));
	QGridLayout *mophology_button_layout = new QGridLayout;
	mophologystyle_buttongroup = new QButtonGroup;
	connect(mophologystyle_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), 
		this, &MorphologyTransformWidget::morphologyTransformImg);
	mophologystyle_buttongroup->setExclusive(true);
	QStringList mophologystylelist;
	mophologystylelist << QString::fromLocal8Bit("��ʴ")
		<< QString::fromLocal8Bit("����")
		<< QString::fromLocal8Bit("������")
		<< QString::fromLocal8Bit("������")
		<< QString::fromLocal8Bit("��̬ѧ�ݶ�")
		<< QString::fromLocal8Bit("��ñ")
		<< QString::fromLocal8Bit("��ñ")
		;
	for (int i = 0; i < 7; i++)
	{
		QRadioButton *pbutton = new QRadioButton(mophologystylelist.at(i));
		if (i == 0)
		{
			pbutton->setChecked(true);
		}
		mophologystyle_buttongroup->setId(pbutton, i);
		mophologystyle_buttongroup->addButton(pbutton);
		if (i%2 != 0)
		{
			mophology_button_layout->addWidget(pbutton, 0, i, 1, 1);
		}
		else
		{
			mophology_button_layout->addWidget(pbutton, 1, i, 1, 1);
		}
	}
	mophology_button_box->setLayout(mophology_button_layout);

	// �ں���״
	QGroupBox *element_button_box = new QGroupBox(QString::fromLocal8Bit("�ں���״"));
	QVBoxLayout *element_button_layout = new QVBoxLayout;
	elementstyle_buttongroup = new QButtonGroup;
	connect(elementstyle_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), 
		this, &MorphologyTransformWidget::morphologyTransformImg);
	elementstyle_buttongroup->setExclusive(true);
	QStringList elementstylelist;
	elementstylelist << "Rect" << "Cross" << "Ellipse";
	for (int i = 0; i < 3; i++)
	{
		QRadioButton *pbutton = new QRadioButton(elementstylelist.at(i));
		if (i == 0)
		{
			pbutton->setChecked(true);
		}
		elementstyle_buttongroup->setId(pbutton, i);
		element_button_layout->addWidget(pbutton);
		elementstyle_buttongroup->addButton(pbutton);
	}
	element_button_box->setLayout(element_button_layout);

	// �ں˴�С������
	QGroupBox *kernelsize_slider_box = new QGroupBox(QString::fromLocal8Bit("�ں˴�С"));
	QHBoxLayout *slider_layout = new QHBoxLayout;
	pslider = new QSlider;
	pslider->setOrientation(Qt::Horizontal);
	pslider->setMinimum(0);
	pslider->setMaximum(21);
	pslider->setTickPosition(QSlider::TicksBelow);
	connect(pslider, &QSlider::valueChanged, this, &MorphologyTransformWidget::morphologyTransformImg);
	slider_value = new QLabel(QString::fromLocal8Bit("�˴�С:0"));
	slider_value->setFixedWidth(60);
	slider_layout->addWidget(slider_value);
	slider_layout->addWidget(pslider);
	kernelsize_slider_box->setLayout(slider_layout);

	main_layout->addWidget(mophology_button_box, 0, 0, 1, 1);
	main_layout->addWidget(element_button_box, 0, 1, 1, 1);
	main_layout->addWidget(kernelsize_slider_box, 1, 0, 1, 2);

	setLayout(main_layout);
}


MorphologyTransformWidget::~MorphologyTransformWidget()
{
}

void MorphologyTransformWidget::morphologyTransformImg()
{
	int kernel_size = pslider->value();
	slider_value->setText(QString::fromLocal8Bit("�˴�С:%1").arg(kernel_size));
	if (!in_img.empty())
	{
		int mophology_style_id = mophologystyle_buttongroup->checkedId();
		int element_style_id = elementstyle_buttongroup->checkedId();
		Mat element = getStructuringElement(-element_style_id - 1, Size(2 * kernel_size + 1, 2 * kernel_size + 1), Point(kernel_size, kernel_size));
		if (mophology_style_id >= -2)
		{
			switch (mophology_style_id)
			{
			case -1:
				erode(in_img, out_img, element);
				emit paramsChanged();
				break;
			case -2:
				dilate(in_img, out_img, element);
				emit paramsChanged();
				break;
			default:
				return;
				break;
			}
		}
		else
		{
			morphologyEx(in_img, out_img, -mophology_style_id - 1, element);
			emit paramsChanged();
		}
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
	
}
