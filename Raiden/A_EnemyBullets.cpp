#include "A_EnemyBullets.h"

//���캯��
A_EnemyBullets::A_EnemyBullets(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit,
	const int& p_BulletMoveSpeed, 
	const double& p_BulletMoveTargetAngle_Sin, const double& p_BulletMoveTargetAngle_Cos) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_BulletMoveSpeed = p_BulletMoveSpeed;
	m_BulletMoveTargetAngle_Cos = p_BulletMoveTargetAngle_Cos;
	m_BulletMoveTargetAngle_Sin = p_BulletMoveTargetAngle_Sin;
}

//��������
A_EnemyBullets::~A_EnemyBullets()
{

}

//����ǰ���󿽱���segBackGround
bool A_EnemyBullets::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b White{ 255, 255, 255 };

	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			White == this->GetImg().at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			//��(first, second)Ϊԭ�㽫this������seg
		}
	}
	re = true;

	return re;
}

//op==����
bool A_EnemyBullets::operator==(A_EnemyBullets Target)
{
	bool re(false);

	if (this->GetPos() == Target.GetPos())
	{
		re = true;
	}
	return re;
}

int A_EnemyBullets::GetBulletMoveSpeed()
{
	return m_BulletMoveSpeed;
}


