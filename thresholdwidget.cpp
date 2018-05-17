#include "thresholdwidget.h"
#include "globalvar.h"
#include <QtWidgets>

using namespace cv;

ThresholdWidget::ThresholdWidget()
{
	QVBoxLayout *main_layout = new QVBoxLayout;
	main_layout->setAlignment(Qt::AlignHCenter);
	// ��ֵ����ѡ��
	QGroupBox *threshtype_box = new QGroupBox(QString::fromLocal8Bit("��ֵ����"));
	threshtype_buttongroup = new QButtonGroup;
	connect(threshtype_buttongroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, &ThresholdWidget::threshImg);
	QStringList threshtypelist;
	threshtypelist << QString::fromLocal8Bit("��������ֵ")
		<< QString::fromLocal8Bit("����������ֵ")
		<< QString::fromLocal8Bit("�ض���ֵ")
		<< QString::fromLocal8Bit("0��ֵ")
		<< QString::fromLocal8Bit("��0��ֵ");
	QHBoxLayout *thresh_type_button_layout = new QHBoxLayout;
	for (int i = 0; i < 5; i++)
	{
		QRadioButton *pbutton = new QRadioButton(threshtypelist.at(i));
		threshtype_buttongroup->setId(pbutton, i);
		if (i == 0)
		{
			pbutton->setChecked(true);
		}
		thresh_type_button_layout->addWidget(pbutton);
		threshtype_buttongroup->addButton(pbutton);
	}
	threshtype_box->setLayout(thresh_type_button_layout);

	// ��ֵ��С������
	QGroupBox *threshold_size_box = new QGroupBox(QString::fromLocal8Bit("��ֵ��С"));
	QHBoxLayout *slider_layout = new QHBoxLayout;
	pslider = new QSlider;
	pslider->setOrientation(Qt::Horizontal);
	pslider->setMinimum(0);
	pslider->setMaximum(255);
	pslider->setTickPosition(QSlider::TicksBelow);
	connect(pslider, &QSlider::valueChanged, this, &ThresholdWidget::threshImg);

	slider_value = new QLabel(QString::fromLocal8Bit("��ֵ��С:0"));
	slider_value->setFixedWidth(80);
	slider_layout->addWidget(slider_value);
	slider_layout->addWidget(pslider);
	threshold_size_box->setLayout(slider_layout);

	main_layout->addWidget(threshtype_box);
	main_layout->addWidget(threshold_size_box);

	setLayout(main_layout);
}


ThresholdWidget::~ThresholdWidget()
{
}

void ThresholdWidget::threshImg()
{
	int threshold_value = pslider->value();
	slider_value->setText(QString::fromLocal8Bit("��ֵ��С:%1").arg(threshold_value));
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			int thresh_style_id = threshtype_buttongroup->checkedId();
			threshold(in_img, out_img, threshold_value, 255, -thresh_style_id - 1);
			emit paramsChanged();
		}
		else
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ת���ҶȰɣ�"), QMessageBox::Yes);
			return;
		}
		
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
}
