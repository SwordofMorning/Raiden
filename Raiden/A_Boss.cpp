#include "A_Boss.h"

//构造函数
A_Boss::A_Boss(std::string p_path,
	int p_health, int p_MoveSpeed,
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_health = p_health;
	m_MoveSpeed = p_MoveSpeed;

	cv::Mat TempImg = this->GetImg().clone();

	for (cv::MatIterator_<cv::Vec3b> it = TempImg.begin<cv::Vec3b>(); it != TempImg.end<cv::Vec3b>(); ++it)
	{
		(*it)[0] = (*it)[0] * 0;
		(*it)[1] = (*it)[1] * 0;
		(*it)[2] = (*it)[2] * 0.8;
	}

	TempImg.copyTo(m_HitImg);

	m_MoveDir = true;
}

//析构函数
A_Boss::~A_Boss()
{

}

//Boss移动
void A_Boss::AutoMove()
{
	int BossPosX = this->GetPos().second;
	int BossPosY = this->GetPos().first;

	//到达左界且向左
	if (BossPosX <= this->GetWidthLowerLimit())
	{
		m_MoveDir = false;
	}
	//到达右界且向右
	else if (BossPosX >= this->GetWidthUpperLimit())
	{
		m_MoveDir = true;
	}

	//Boss开火
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 8);
	int num = dis(gen);

	if (num == 1 && this->m_BulletObjList.size() < 5)
	{
		this->BossAutoFire();
	}

	//Boss移动
	if (m_MoveDir)
	{
		//this->MovePos(0, 0 - m_MoveSpeed);
		this->SetPos(this->GetPos().first, this->GetPos().second - 10);
	}
	else if (!m_MoveDir)
	{
		this->MovePos(0, m_MoveSpeed);
	}
}

//Boss开火
void A_Boss::BossAutoFire()
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

//将当前对象拷贝到segBackGround
bool A_Boss::Segmentation(cv::Mat& segBackGround)
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

//Boss子弹移动
bool A_Boss::BossBulletMove()
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

//Boss血量减少
void A_Boss::BossHealthReduce()
{
	m_health--;
}

//Boss存活判断
bool A_Boss::IsBossAlive()
{
	bool re(true);
	this->m_health >= 0 ? 
		re = true : 
		re = false;
	return re;
}

//被击中特效
void A_Boss::Hitted()
{
	this->SetImg(m_HitImg);
}

//爆炸特效
void A_Boss::ActorBoom1()
{
	this->SetImg(cv::imread(".\\Source\\Re_Effects\\BossBoom1.png", 1));
}

//爆炸特效
void A_Boss::ActorBoom2()
{
	this->SetImg(cv::imread(".\\Source\\Re_Effects\\BossBoom2.png", 1));
}

//返回血量
int A_Boss::GetHealth()
{
	return m_health;
}

//检测：玩家 碰 Boss子弹
bool A_Boss::CollionPlayerWithBossBullet(A_PlayerFighter Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
