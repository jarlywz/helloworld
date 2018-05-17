#include "inoutimgwidget.h"
#include <globalvar.h>
#include <QtWidgets>
#include <QFileDialog>

using namespace cv;

InOutImgWidget::InOutImgWidget()
{
	out_img_index = 1;
	QVBoxLayout *main_layout = new QVBoxLayout;
	// ����ͼ��
	QGroupBox *in_img_box = new QGroupBox(QString::fromLocal8Bit("����ͼ��"));
	QGridLayout *in_img_layout = new QGridLayout;
	in_img_label = new QLabel();
	in_img_label->setAlignment(Qt::AlignCenter);
	in_img_label->setFixedSize(320, 240);
	load_img_button = new QPushButton(QString::fromLocal8Bit("����ͼ��"));
	connect(load_img_button, &QPushButton::clicked, this, &InOutImgWidget::loadImg);
	to_gray_button = new QPushButton(QString::fromLocal8Bit("ת�Ҷ�ͼ"));
	connect(to_gray_button, &QPushButton::clicked, this, &InOutImgWidget::cvtGray);
	//equalizehist_button = new QPushButton(QString::fromLocal8Bit("ֱ��ͼ���⻯"));
	//connect(equalizehist_button, &QPushButton::clicked, this, &InOutImgWidget::m_equalizeHist);

	in_img_layout->addWidget(in_img_label, 0, 0, 1, 2);
	in_img_layout->addWidget(load_img_button, 1, 0, 1, 1);
	in_img_layout->addWidget(to_gray_button, 1, 1, 1, 1);
	//in_img_layout->addWidget(equalizehist_button, 1, 2, 1, 1);
	in_img_box->setLayout(in_img_layout);
	// ���ͼ��
	QGroupBox *out_img_box = new QGroupBox(QString::fromLocal8Bit("���ͼ��"));
	QGridLayout *out_img_layout = new QGridLayout;
	out_img_label = new QLabel();
	out_img_label->setAlignment(Qt::AlignCenter);
	out_img_label->setFixedSize(320, 240);
	save_img_button = new QPushButton(QString::fromLocal8Bit("����ͼ��"));
	connect(save_img_button, &QPushButton::clicked, this, &InOutImgWidget::saveOutImg);
	to_in_img_button = new QPushButton(QString::fromLocal8Bit("����Ϊ����ͼ��"));
	connect(to_in_img_button, &QPushButton::clicked, this, &InOutImgWidget::cvtInimg);
	out_img_layout->addWidget(out_img_label, 0, 0, 1, 2);
	out_img_layout->addWidget(save_img_button, 1, 0, 1, 1);
	out_img_layout->addWidget(to_in_img_button, 1, 1, 1, 1);
	out_img_box->setLayout(out_img_layout);

	
	main_layout->addWidget(in_img_box);
	main_layout->addWidget(out_img_box);
	setLayout(main_layout);
}

InOutImgWidget::~InOutImgWidget()
{
}

// MatתQImage
QImage cvMat2QImage(const Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1  
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat  
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}
// ����ͼ��
void InOutImgWidget::loadImg()
{
	img_path = QFileDialog::getOpenFileName(this, tr("open file"), "C:\\Users\\Daiwenzhang\\Desktop\\TestImg", tr("Image files(*.jpg)"));
	in_img = imread(img_path.toStdString());
	if (!in_img.empty())
	{
		//cvtColor(in_img, in_img, COLOR_BGR2RGB);
		qimg = cvMat2QImage(in_img);
		float ratio = in_img.size().width / in_img.size().height;
		if (ratio>4 / 3)
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToWidth(320));
		}
		else
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToHeight(240));
		}
		out_img_index = 1;
	}
	else
	{
		return;
	}
}
// תΪ�Ҷ�ͼ
void InOutImgWidget::cvtGray()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬�Ѿ��ǻҶ���������"), QMessageBox::Yes);
			return;
		}
		cvtColor(in_img, in_img, COLOR_RGB2GRAY);
		qimg = cvMat2QImage(in_img);
		float ratio = in_img.size().width / in_img.size().height;
		if (ratio>4 / 3)
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToWidth(320));
		}
		else
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToHeight(240));
		}
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
}
// ֱ��ͼ���⻯
//void InOutImgWidget::m_equalizeHist()
//{
//	if (!in_img.empty())
//	{
//		if (in_img.channels() == 1)
//		{
//			equalizeHist(in_img, in_img);
//			qimg = cvMat2QImage(in_img);
//			float ratio = in_img.size().width / in_img.size().height;
//			if (ratio>4 / 3)
//			{
//				in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToWidth(320));
//			}
//			else
//			{
//				in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToHeight(240));
//			}
//		}
//		else
//		{
//			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ת���ҶȰɣ�"), QMessageBox::Yes);
//			return;
//		}
//	}
//	else
//	{
//		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
//		return;
//	}
//}
// ���ͼתΪ����ͼ
void InOutImgWidget::cvtInimg()
{
	if (!out_img.empty())
	{
		in_img = out_img.clone();
		qimg = cvMat2QImage(in_img);
		float ratio = in_img.size().width / in_img.size().height;
		if (ratio>4 / 3)
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToWidth(320));
		}
		else
		{
			in_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToHeight(240));
		}
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
}
// ���浱ǰ���ͼ
void InOutImgWidget::saveOutImg()
{

	if (!out_img.empty())
	{
		QString imgtotalname = *(img_path.split("/").constEnd() - 1);
		QString imgname = QString(imgtotalname).remove(*(QString(imgtotalname).split(".").constEnd() - 1)).remove(".");
		QString imgtype = *(QString(imgtotalname).split(".").constEnd() - 1);
		QString backspace = QString(img_path).remove(*(img_path.split("/").constEnd() - 1));
		QString out_img_path = backspace + imgname + "_" + QString::number(out_img_index, 10) + "." + imgtype;
		QFile file(out_img_path);
		if (file.exists())
		{
			int rtn = QMessageBox::question(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�ϸ磬�ļ��Ѵ��ڣ�Ҫ���ǲ���"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if (rtn == QMessageBox::Yes)
			{
				imwrite(out_img_path.toStdString(), out_img);
				out_img_index += 1;
			}
			else
			{
				return;
			}
		}
		else
		{
			imwrite(out_img_path.toStdString(), out_img);
			out_img_index += 1;
		}
	}
	else
	{
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("�ϸ磬ûͼ����"), QMessageBox::Yes);
		return;
	}
}
// ���µ��κ�����ͼ
void InOutImgWidget::updateOutImg()
{
	if (!out_img.empty())
	{
		imshow("���ͼ", out_img);
		qimg = cvMat2QImage(out_img);
		float ratio = out_img.size().width / out_img.size().height;
		if (ratio>4 / 3)
		{
			out_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToWidth(320));
		}
		else
		{
			out_img_label->setPixmap(QPixmap::fromImage(qimg).scaledToHeight(240));
		}
	}
	else
	{
		return;
	}
}