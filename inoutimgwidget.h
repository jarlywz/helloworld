#pragma once
#include <QWidget>
#include <QString>

class QLabel;
class QPushButton;



class InOutImgWidget:public QWidget
{
	Q_OBJECT
public:
	InOutImgWidget();
	~InOutImgWidget();
	// 载入图像
	void loadImg();
	// 转为灰度
	void cvtGray();
	// 直方图均衡化
	//void m_equalizeHist();
	// 输出转为输入
	void cvtInimg();
	// 保存输出图
	void saveOutImg();
	// 更新调参后的输出图
	void updateOutImg();
private:
	QString img_path;                  // 输入图路径
	int out_img_index;                 // 保存文件名编号
	QImage qimg;
	QLabel *in_img_label;              // 输入图区域
	QLabel *out_img_label;             // 输出图区域
	QPushButton *load_img_button;      // 载入图像按钮
	QPushButton *to_gray_button;       // 转为灰度图按钮
	//QPushButton *equalizehist_button;  // 直方图均衡化按钮
	QPushButton *save_img_button;      // 保存图像按钮
	QPushButton *to_in_img_button;     // 转为输入图按钮
};

