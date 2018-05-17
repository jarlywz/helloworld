#include "inoutimgwidget.h"
#include <globalvar.h>
#include <QtWidgets>
#include <QFileDialog>

using namespace cv;

InOutImgWidget::InOutImgWidget()
{
	out_img_index = 1;
	QVBoxLayout *main_layout = new QVBoxLayout;
	// 输入图像
	QGroupBox *in_img_box = new QGroupBox(QString::fromLocal8Bit("输入图像"));
	QGridLayout *in_img_layout = new QGridLayout;
	in_img_label = new QLabel();
	in_img_label->setAlignment(Qt::AlignCenter);
	in_img_label->setFixedSize(320, 240);
	load_img_button = new QPushButton(QString::fromLocal8Bit("载入图像"));
	connect(load_img_button, &QPushButton::clicked, this, &InOutImgWidget::loadImg);
	to_gray_button = new QPushButton(QString::fromLocal8Bit("转灰度图"));
	connect(to_gray_button, &QPushButton::clicked, this, &InOutImgWidget::cvtGray);
	//equalizehist_button = new QPushButton(QString::fromLocal8Bit("直方图均衡化"));
	//connect(equalizehist_button, &QPushButton::clicked, this, &InOutImgWidget::m_equalizeHist);

	in_img_layout->addWidget(in_img_label, 0, 0, 1, 2);
	in_img_layout->addWidget(load_img_button, 1, 0, 1, 1);
	in_img_layout->addWidget(to_gray_button, 1, 1, 1, 1);
	//in_img_layout->addWidget(equalizehist_button, 1, 2, 1, 1);
	in_img_box->setLayout(in_img_layout);
	// 输出图像
	QGroupBox *out_img_box = new QGroupBox(QString::fromLocal8Bit("输出图像"));
	QGridLayout *out_img_layout = new QGridLayout;
	out_img_label = new QLabel();
	out_img_label->setAlignment(Qt::AlignCenter);
	out_img_label->setFixedSize(320, 240);
	save_img_button = new QPushButton(QString::fromLocal8Bit("保存图像"));
	connect(save_img_button, &QPushButton::clicked, this, &InOutImgWidget::saveOutImg);
	to_in_img_button = new QPushButton(QString::fromLocal8Bit("保存为输入图像"));
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

// Mat转QImage
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
// 载入图像
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
// 转为灰度图
void InOutImgWidget::cvtGray()
{
	if (!in_img.empty())
	{
		if (in_img.channels() == 1)
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，已经是灰度啦！！！"), QMessageBox::Yes);
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
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
		return;
	}
}
// 直方图均衡化
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
//			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，转个灰度吧！"), QMessageBox::Yes);
//			return;
//		}
//	}
//	else
//	{
//		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
//		return;
//	}
//}
// 输出图转为输入图
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
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
		return;
	}
}
// 保存当前输出图
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
			int rtn = QMessageBox::question(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("老哥，文件已存在，要覆盖不？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
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
		QMessageBox::warning(this, "warning", QString::fromLocal8Bit("老哥，没图啊！"), QMessageBox::Yes);
		return;
	}
}
// 更新调参后的输出图
void InOutImgWidget::updateOutImg()
{
	if (!out_img.empty())
	{
		imshow("输出图", out_img);
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