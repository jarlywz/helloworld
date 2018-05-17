#include "filterwidget.h"
#include "globalvar.h"
#include <QtWidgets>
#include <QDebug>

using namespace cv;

FilterWidget::FilterWidget()
{
	QGridLayout *main_layout = new QGridLayout;

	// �˲�����ѡ��
	QGroupBox *filter_type_box = new QGroupBox(QString::fromLocal8Bit("�˲�����"));
	QHBoxLayout *filter_button_layout = new QHBoxLayout;
	filterstyle_buttongroup = new QButtonGroup;
	connect(filterstyle_buttongroup,static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &FilterWidget::filteImg);
	filterstyle_buttongroup->setExclusive(true);
	QStringList blurstylelist;
	blurstylelist << QString::fromLocal8Bit("��ֵ�˲�")
		<< QString::fromLocal8Bit("��˹�˲�")
		<< QString::fromLocal8Bit("��ֵ�˲�")
		<< QString::fromLocal8Bit("˫���˲�");
	for (int i = 0; i < 4; i++)
	{
		QRadioButton *pbutton = new QRadioButton(blurstylelist.at(i));
		if (i == 0)
		{
			pbutton->setChecked(true);
		}
		filterstyle_buttongroup->setId(pbutton, i);
		filterstyle_buttongroup->addButton(pbutton);
		filter_button_layout->addWidget(pbutton);
	}
	filter_type_box->setLayout(filter_button_layout);

	// �˴�С������
	QGroupBox *kernel_size_box = new QGroupBox(QString::fromLocal8Bit("�˴�С"));
	QHBoxLayout *slider_layout = new QHBoxLayout;
	pslider = new QSlider;
	pslider->setOrientation(Qt::Horizontal);
	pslider->setMinimum(1);
	pslider->setMaximum(31);
	pslider->setSingleStep(2);
	pslider->setTickPosition(QSlider::TicksBelow);
	connect(pslider, &QSlider::valueChanged, this, &FilterWidget::filteImg);

	slider_value = new QLabel(QString::fromLocal8Bit("�˴�С:1"));
	slider_layout->addWidget(slider_value);
	slider_layout->addWidget(pslider);
	kernel_size_box->setLayout(slider_layout);

	main_layout->addWidget(filter_type_box, 0, 0, 1, 1);
	main_layout->addWidget(kernel_size_box, 1, 0, 1, 1);
	setLayout(main_layout);
}

FilterWidget::~FilterWidget()
{
}
// ������ͼ�����˲�
void FilterWidget::filteImg()
{
	int kernel_size = pslider->value();
	if (kernel_size % 2 == 0)
	{
		return;
	}
	slider_value->setText(QString::fromLocal8Bit("�˴�С:%1").arg(kernel_size));
	if (!in_img.empty())
	{
		int filter_style_id = filterstyle_buttongroup->checkedId();
		switch (filter_style_id)
		{
		case -1:
			blur(in_img, out_img, Size(kernel_size, kernel_size), Point(-1, -1));
			emit paramsChanged();
			break;
		case -2:
			GaussianBlur(in_img, out_img, Size(kernel_size, kernel_size), 0, 0);
			emit paramsChanged();
			break;
		case -3:
			medianBlur(in_img, out_img, kernel_size);
			emit paramsChanged();
			break;
		case -4:
			bilateralFilter(in_img, out_img, kernel_size, kernel_size * 2, kernel_size / 2);
			emit paramsChanged();
			break;
		default:
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ѡ���˲����£�"), QMessageBox::Yes);
			break;
		}
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
}
