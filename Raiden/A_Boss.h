#pragma once

#include "A_Actor.h"
#include "A_EnemyBullets.h"
#include "A_PlayerFighter.h"

class A_PlayerFighter;
class A_EnemyBullets;

class A_Boss : public A_Actor
{
private:
	int m_health;																//Boss血量

	std::vector<A_EnemyBullets> m_BulletObjList;								//用于存放战机生成的炮弹

	bool m_MoveDir;																//移动方向 true左false右
	
	int m_MoveSpeed;															//移动速度

	cv::Mat m_HitImg;															//被击中的照片
public:
	A_Boss(std::string p_path = ".\\Source\\Re_Boss\\Boss_01.png",
		int p_health = 50, int p_MoveSpeed = 10,
		const int& p_height = 0, const int& p_width = 150,
		const int& p_HeightLowerLimit = 0,
		const int& p_HeightUpperLimit = BackGroundScale.first - 500,
		const int& p_WidthLowerLimit = 10,
		const int& p_WidthUpperLimit = BackGroundScale.second - 510);									//构造函数

	~A_Boss();																							//析构函数

	void AutoMove();																					//Boss自动移动

	void BossAutoFire();																				//Boss开火

	bool Segmentation(cv::Mat& segBackGround) override;													//将当前对象拷贝到segBackGround

	bool BossBulletMove();																				//Boss子弹移动

	void BossHealthReduce();																			//Boss血量减少

	bool IsBossAlive();																					//Boss存活判断

	void Hitted();																						//Boss被击中

	 void ActorBoom1() override;																		//爆炸特效

	 void ActorBoom2() override;																		//爆炸特效

	 int GetHealth();																					//返回血量

	/*--- 碰撞检测 ---*/
	bool CollionPlayerWithBossBullet(A_PlayerFighter Target);											//检测：玩家 碰 Boss子弹

};


