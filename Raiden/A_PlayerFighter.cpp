#include "A_PlayerFighter.h"

extern const std::pair<int, int> PlayerFighterScale;
extern const std::vector<std::pair<int, int>> BulletScale;

/*=== 成员函数 ===*/

//构造函数
A_PlayerFighter::A_PlayerFighter(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit, 
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) : 
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_BulletLevel = m_BulletLevelLowerLimit;
	m_Health = m_HealthAtBegin;

	//炮弹图片路径
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_0.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_1.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_2.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_3.png"));
}

//析构函数
A_PlayerFighter::~A_PlayerFighter()
{

}

//复制构造函数
A_PlayerFighter::A_PlayerFighter(const A_PlayerFighter& Target) : A_Actor(Target)
{
	m_BulletLevel = m_BulletLevelLowerLimit;
	m_Health = m_HealthAtBegin;
}

//opera= 重载
A_PlayerFighter A_PlayerFighter::operator=(const A_PlayerFighter& Target)
{
	A_PlayerFighter re(Target);
	return re;
}

//左键开火函数
void A_PlayerFighter::PlayerFighterFire_LeftClick()
{
	//在FIghter前方生存炮弹
	int BulletParaX = this->GetPos().second + PlayerFighterScale.second / 2;				//width居中
	int BulletParaY = this->GetPos().first - BulletScale[m_BulletLevel].first;				//height - BulletScale.height(160)

	A_Bullet newBullet(m_BulletImgPath[m_BulletLevel], BulletParaY, BulletParaX);

	if (!(newBullet.GetPos().first < newBullet.GetHeightLowerLimit()))
	{
		//不小于上界则合法
		m_BulletObjList.push_back(newBullet);
	}

	PlaySound(".\\Source\\Re_Sound\\PlayerFire.wav", NULL, SND_ASYNC);
}

//将当前对象 和 子弹拷贝到segBackGround
bool A_PlayerFighter::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b White{ 255, 255, 255 };
	cv::Vec3b Black{ 0, 0, 0 };

	//绘制飞机
	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			//以(first, second)为原点将this拷贝到seg
			if (White != this->GetImg().at<cv::Vec3b>(i, j) && Black != this->GetImg().at<cv::Vec3b>(i, j))
			{
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			}
		}
	}

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

//飞机所有子弹移动
bool A_PlayerFighter::BulletMove()
{
	if (!this->m_BulletObjList.empty())
	{
		//子弹移动
		for (auto it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
		{
			it->MovePos(-(it->GetBulletMoveSpeed()), 0);
		}
	}

	//排序准则
	BulletOrderOP op;
	std::sort(this->m_BulletObjList.begin(), this->m_BulletObjList.end(), op);

	//子弹删除
	for (std::vector<A_Bullet>::iterator it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
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

//判断玩家血量是否结束游戏
bool A_PlayerFighter::IsAlive()
{
	bool re(true);
	m_Health > 0 ? re = true : re = false;
	return re;
}

//子弹等级
void A_PlayerFighter::SetBulletLevel(int p_level)
{
	m_BulletLevel = p_level;
}

//检测：玩家 碰 敌人
bool A_PlayerFighter::CollionFighterWithEnemy(A_Enemy Target)
{
	bool re(false);
	re = this->RectangleCollision(Target);
	return re;
}

//检测：敌人 碰 玩家子弹
bool A_PlayerFighter::CollionEnemyWithBullet(A_Enemy Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}

//检测：Boss 碰 玩家子弹
bool A_PlayerFighter::CollionBossWithBullet(A_Boss Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
