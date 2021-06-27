#pragma once

#include <opencv.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "A_Actor.h"
#include "A_Bullet.h"
#include "A_Enemy.h"
#include "A_EnemyBullets.h"
#include "A_Boss.h"

extern const std::pair<int, int> PlayerFighterScale;
extern const std::vector<std::pair<int, int>> BulletScale;

class A_Enemy;
class A_Boss;
class A_Bullet;

//子弹排序准则
class BulletOrderOP;

/*=== 玩家战机类 ===*/
class A_PlayerFighter :public A_Actor
{
private:	
	/*--- 飞机属性 ---*/
	const int m_HealthAtBegin = 5;						//开局5条命
	int m_Health;										//当前血量

	/*--- 飞机炮弹 ---*/
	std::vector<std::string> m_BulletImgPath;			//炮弹图形数组（升级机制）
	int m_BulletLevel;									//当前炮弹等级
	const int m_BulletLevelLowerLimit = 0;				//炮弹等级下界
	const int m_BulletLevelUpperLimit = 3;				//炮弹等级上界
	std::vector<A_Bullet> m_BulletObjList;				//用于存放战机生成的炮弹

public:
	A_PlayerFighter(std::string p_path = ".\\Source\\Re_PlayerFighter\\PlayerFighter_01.png",
		const int& p_height = 500, const int& p_width = 350,
		const int& p_HeightLowerLimit = 20,
		const int& p_HeightUpperLimit = BackGroundScale.first - 20,
		const int& p_WidthLowerLimit = 20,
		const int& p_WidthUpperLimit = BackGroundScale.second - 20);								//构造函数

	~A_PlayerFighter();																				//析构函数

	A_PlayerFighter(const A_PlayerFighter& Target);													//复制构造函数

	A_PlayerFighter operator=(const A_PlayerFighter& Target);										//opera= 重载

	void PlayerFighterFire_LeftClick();																//左键开火函数

	bool Segmentation(cv::Mat& segBackGround) override;												//将当前对象 和 子弹拷贝到segBackGround

	bool BulletMove();																				//飞机所有子弹移动

	bool IsAlive();																					//判断玩家血量是否结束游戏

	void SetBulletLevel(int p_level);																//子弹等级

	/*--- 碰撞检测系列 ---*/
	bool CollionFighterWithEnemy(A_Enemy Target);													//检测：玩家 碰 敌人

	bool CollionEnemyWithBullet(A_Enemy Target);													//检测：敌人 碰 玩家子弹

	bool CollionBossWithBullet(A_Boss Target);														//检测：Boss 碰 玩家子弹

};

class BulletOrderOP
{
public:
	bool operator()(A_Bullet A, A_Bullet B)
	{
		return A.GetPos().first < B.GetPos().first;
	}
};