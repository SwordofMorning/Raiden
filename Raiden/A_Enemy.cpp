#include "A_Enemy.h"

A_Enemy::A_Enemy(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_Alive = true;
}

//析构函数
A_Enemy::~A_Enemy()
{

}


bool A_Enemy::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b Black{ 0, 0, 0 };

	//绘制敌人
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

	//绘制敌人子弹

	if (!this->m_BulletObjList.empty())
	{
		for (auto i : m_BulletObjList)
		{
			i.Segmentation(segBackGround);
		}
	}
	re = true;

	return re;
}

//敌人移动
void A_Enemy::EnemyAutoMovie()
{
	int para_height = 10;
	int para_width = 0;
	//向下移动

	/*--- 移动时开火 ---*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10);
	int num = dis(gen);

	// 1/10的几率开火 且一次最多1发
	if (num == 1 && m_BulletObjList.size() < 2)
	{
		this->EnemyFire();
	}

	//移动
	this->MovePos(para_height, para_width);
}

//自我销毁函数（对象碰撞游戏边界时发生）
bool A_Enemy::DestoryObj()
{
	bool re(false);

	if (this->GetPos().first >= this->GetHeightUpperLimit())		//到达下界
	{
		this->~A_Enemy();
		re = true;
	}

	return re;
}

//敌人开火
void A_Enemy::EnemyFire()
{
	//在FIghter前方生存炮弹	
	int BulletParaX = this->GetPos().second + this->GetImg().size().width / 2;				//width居中
	int BulletParaY = this->GetPos().first + this->GetImg().size().height;					//height - BulletScale.height(160)

	A_EnemyBullets newBullet(".\\Source\\Re_EnemyBullets\\EnemyHit.png",
		BulletParaY, BulletParaX);

	if (!(newBullet.GetPos().first > newBullet.GetHeightUpperLimit()))
	{
		//不大于上界则合法
		m_BulletObjList.push_back(newBullet);
	}
}

//敌人子弹移动
bool A_Enemy::EnemyBulletMove()
{
	if (!this->m_BulletObjList.empty())
	{
		//子弹移动
		for (auto it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
		{
			it->MovePos((it->GetBulletMoveSpeed()), 0);
		}
	}

	//子弹删除
	for (std::vector<A_EnemyBullets>::iterator it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
	{
		if (it->DestoryObj())
		{
			m_BulletObjList.erase(std::remove(m_BulletObjList.begin(), m_BulletObjList.end(), *it), m_BulletObjList.end());
		}
		break;
		/*--- 这里break是因为一次只删一个 ---*/
	}
	/*--- 已知bug:必须从头到尾删除 ---*/

	return true;
}

//获取子弹信息
std::vector<A_EnemyBullets> A_Enemy::GetBulletObj()
{
	return m_BulletObjList;
}

//设置子弹信息
void A_Enemy::SetBulletObj(std::vector<A_EnemyBullets> para)
{
	m_BulletObjList = para;
}



//检测：玩家 碰 敌人子弹
bool A_Enemy::CollionEnemyBulletWithPlayer(A_PlayerFighter Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
