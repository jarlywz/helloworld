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
	// ����ͼ��
	void loadImg();
	// תΪ�Ҷ�
	void cvtGray();
	// ֱ��ͼ���⻯
	//void m_equalizeHist();
	// ���תΪ����
	void cvtInimg();
	// �������ͼ
	void saveOutImg();
	// ���µ��κ�����ͼ
	void updateOutImg();
private:
	QString img_path;                  // ����ͼ·��
	int out_img_index;                 // �����ļ������
	QImage qimg;
	QLabel *in_img_label;              // ����ͼ����
	QLabel *out_img_label;             // ���ͼ����
	QPushButton *load_img_button;      // ����ͼ��ť
	QPushButton *to_gray_button;       // תΪ�Ҷ�ͼ��ť
	//QPushButton *equalizehist_button;  // ֱ��ͼ���⻯��ť
	QPushButton *save_img_button;      // ����ͼ��ť
	QPushButton *to_in_img_button;     // תΪ����ͼ��ť
};

