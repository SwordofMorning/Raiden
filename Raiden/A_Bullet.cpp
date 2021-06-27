#include "A_Bullet.h"

//构造函数
A_Bullet::A_Bullet(std::string p_path,
	const int& p_height, const int& p_width,
	const int& p_HeightLowerLimit,const int& p_HeightUpperLimit, 
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit,
	const int& p_BulletMoveSpeed, 
	const double& p_BulletMoveTargetAngle_Sin, 
	const double& p_BulletMoveTargetAngle_Cos) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_BulletMoveSpeed = p_BulletMoveSpeed;
	m_BulletMoveTargetAngle_Cos = p_BulletMoveTargetAngle_Cos;
	m_BulletMoveTargetAngle_Sin = p_BulletMoveTargetAngle_Sin;
}

//析构函数
A_Bullet::~A_Bullet()
{

}

//将当前对象拷贝到segBackGround
bool A_Bullet::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b Black{ 0, 0, 0 };

	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			Black == this->GetImg().at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			//以(first, second)为原点将this拷贝到seg
		}
	}
	re = true;

	return re;
}

//自我销毁函数（对象碰撞游戏边界时发生）
bool A_Bullet::DestoryObj()
{
	bool re(false);

	//玩家子弹是否销毁只用判断上界
	if (this->GetPos().first <= this->GetHeightLowerLimit())			//到达上界
	{
		//不能再向上：destory
		this->~A_Bullet();
		re = true;
	}

	return re;
}

//op==重载
bool A_Bullet::operator==(A_Bullet Target)
{
	bool re(false);
	
	if (this->GetPos() == Target.GetPos() )
	{
		re = true;
	}
	return re;
}

//返回m_BulletMoveSpeed
int A_Bullet::GetBulletMoveSpeed()
{
	return m_BulletMoveSpeed;
}