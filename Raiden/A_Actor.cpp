#include "A_Actor.h"

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;

//���캯��
A_Actor::A_Actor(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit)
{
	/*--- ��ɫͼ�� ---*/
	m_Img = cv::imread(p_path, 1);											//��ɫͼ��
	m_ImgClone = m_Img.clone();												//��ɫͼ��ı���(const)

	/*--- ���α߿� ---*/
	m_Pos.first = p_height;													//��ɫλ��(����)��first == height, second = Width
	m_Pos.second = p_width;
	m_PosLeftDown.first = m_Pos.first + m_Img.size().height;				//��ײ�������½ǣ�height = ����h + size.height
	m_PosLeftDown.second = m_Pos.second;									//                width = ����w
	m_PosRightUp.first = m_Pos.first;										//��ײ�������Ͻǣ�height = ����h
	m_PosRightUp.second = m_Pos.second + m_Img.size().width;				//                width = ����w + size.width

	/*--- ��ɫ�ƶ��߽� ---*/
	m_HeightLowerLimit = p_HeightLowerLimit;
	m_HeightUpperLimit = p_HeightUpperLimit;
	m_WidthLowerLimit = p_WidthLowerLimit;
	m_WidthUpperLimit = p_WidthUpperLimit;

	/*--- ��ײ��⻺���� ---*/
	m_CollionBuffer = cv::Mat::zeros(cv::Size(BackGroundScale.second, BackGroundScale.first), CV_8UC3);
}

//��������
A_Actor::~A_Actor()
{
	m_Img.release();
	m_ImgClone.release();
	m_CollionBuffer.release();
	//�ͷ�
}

//�������ٺ�����������ײ��Ϸ�߽�ʱ������
bool A_Actor::DestoryObj()
{
	bool re(false);
	//�����ж�
	if (this->m_Pos.second <= m_WidthLowerLimit)			//�������
	{
		this->~A_Actor();
		re = true;
	}
	else if (this->m_Pos.second >= m_WidthUpperLimit)		//�����ҽ�
	{
		this->~A_Actor();
		re = true;
	}

	//�����ж�
	if (this->m_Pos.first <= m_HeightLowerLimit)			//�����Ͻ�
	{
		this->~A_Actor();
		re = true;
	}
	else if (this->m_Pos.first >= m_HeightUpperLimit)		//�����½�
	{
		this->~A_Actor();
		re = true;
	}

	return re;
}

//����ǰ���󿽱���segBackGround
bool A_Actor::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b White{ 255, 255, 255 };

	for (int i(0); i < this->m_Img.size().height; ++i)
	{
		for (int j(0); j < this->m_Img.size().width; ++j)
		{
			White == this->m_Img.at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->m_Pos.first, j + this->m_Pos.second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->m_Pos.first, j + this->m_Pos.second) = this->m_Img.at<cv::Vec3b>(i, j);
			//��(first, second)Ϊԭ�㽫this������seg
		}
	}
	re = true;

	return re;
}

//�ƶ���ǰ��ɫ
bool A_Actor::MovePos(int p_height, int p_width)
{
	bool re(false);

	//�����ж�
	if (this->m_Pos.second <= m_WidthLowerLimit)			//�������
	{
		//����������p_width >=0
		p_width < 0 ? p_width = 0 : p_width;
	}
	else if (this->m_Pos.second >= m_WidthUpperLimit)		//�����ҽ�
	{
		//���������ң�p_width <=0
		p_width > 0 ? p_width = 0 : p_width;
	}

	//�����ж�
	if (this->m_Pos.first <= m_HeightLowerLimit)			//�����Ͻ�
	{
		//���������ϣ�p_height >=0
		p_width < 0 ? p_width = 0 : p_width;
	}
	else if (this->m_Pos.first >= m_HeightUpperLimit)		//�����½�
	{
		//���������£�p_height <=0
		p_width > 0 ? p_width = 0 : p_width;
	}

	re = true;

	m_Pos.first += p_height;
	m_Pos.second += p_width;
	return re;
}

//���õ�ǰ��ɫλ��
bool A_Actor::SetPos(const int& p_height, const int& p_width)
{
	m_Pos.first = p_height;
	m_Pos.second = p_width;
	return false;
}

//����ͼƬ
void A_Actor::SetImg(cv::Mat Temp)
{
	Temp.copyTo(m_Img);
}

/*
	=== ��ײ����㷨 ===
��1��ѡ����Ҫ�����������顣
��2���ȼ�����������Ƿ�����Χ����ײ�����û�����˳��������ȡ�������ε��ཻ���򣬲�������
��3����һ��������Ƶ�����Ϸ��Ļ�ȴ�Ŀհ׵ĺ�̨�������У���ȡ�����������ཻ������������ݡ�
��4�������̨��������
��5������һ��������в���3�Ĳ�����
��6���õ�����������ͬһ���ཻ���ε��������ݺ�ѭ���Ƚ�ÿһ�����ص㣬�������������ͬһλ�õ�͸���Ȳ�����0�����ʾ�����������ཻ���˳�ѭ���������档
*/

//������ײ����㷨
bool A_Actor::RectangleCollision(A_Actor Target)
{
	bool re(false);

	m_CollionBuffer = cv::Mat::zeros(cv::Size(BackGroundScale.second, BackGroundScale.first), CV_8UC3);
	//ˢ�»�����

	//�������y��x
	int MaxLeftDownHeight = std::max(this->m_PosLeftDown.first, Target.m_PosLeftDown.first);
	int MaxLeftDownWidth = std::max(this->m_PosLeftDown.second, Target.m_PosLeftDown.second);
	//��С����y��x
	int MinRightUpHeight = std::min(this->m_PosRightUp.first, Target.m_PosRightUp.first);
	int MinRightUpWidth = std::min(this->m_PosRightUp.second, Target.m_PosRightUp.second);

	//������
	if (!((MaxLeftDownWidth > MinRightUpWidth) || (MaxLeftDownHeight < MinRightUpHeight)))
	{
		re = this->PixelCollision(Target);
	}

	return re;
}

//������ײ����㷨
bool A_Actor::PixelCollision(A_Actor Target)
{
	bool re(false);

	//��Target������������
	Target.Segmentation(this->m_CollionBuffer);

	//��黺����
	for (int i(0); i < this->m_Img.size().height; ++i)
	{
		for (int j(0); j < this->m_Img.size().width; ++j)
		{
			if (m_CollionBuffer.at<cv::Vec3b>(m_Pos.first + i, m_Pos.second + j) != cv::Vec3b(0, 0, 0))
			{
				re = true;
			}
		}
	}

	return re;
}

//��ը��Ч
void A_Actor::ActorBoom1()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom1.png", 1);
}

//��ը��Ч
void A_Actor::ActorBoom2()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom2.png", 1);
}

//��ը��Ч
void A_Actor::ActorBoom3()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom3.png", 1);
}

//ͼ��ԭ
void A_Actor::ImgRecover()
{
	m_ImgClone.copyTo(m_Img);
}

//��ȡͼ��m_Img
cv::Mat A_Actor::GetImg()
{
	return this->m_Img;
}

//��ȡ��ɫλ��m_Pos
std::pair<int, int> A_Actor::GetPos()
{
	return this->m_Pos;
}

//��ȡ��ɫ�ƶ��߽�
int A_Actor::GetHeightLowerLimit()
{
	return m_HeightLowerLimit;
}

//��ȡ��ɫ�ƶ��߽�
int A_Actor::GetHeightUpperLimit()
{
	return m_HeightUpperLimit;
}

//��ȡ��ɫ�ƶ��߽�
int A_Actor::GetWidthLowerLimit()
{
	return m_WidthLowerLimit;
}

//��ȡ��ɫ�ƶ��߽�
int A_Actor::GetWidthUpperLimit()
{
	return m_WidthUpperLimit;
}
