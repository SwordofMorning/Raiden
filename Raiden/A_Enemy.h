#pragma once
#include <vector>
#include <random>
#include "A_Actor.h"
#include "A_PlayerFighter.h"
#include "A_EnemyBullets.h"

class A_EnemyBullets;
class A_PlayerFighter;

extern const std::pair<int, int> EnemyHitSacle;

class A_Enemy :	public A_Actor
{
private:
	std::vector<A_EnemyBullets> m_BulletObjList;								//用于存放战机生成的炮弹

	bool m_Alive;																//判断敌人是否存活 => 敌人与玩家子弹的碰撞检测在A_PlayerFighter类中完成
public:
	
	A_Enemy(std::string p_path = ".\\Source\\Re_Enemy\\Enemy_01.png",
		const int& p_height = 200, const int& p_width = 350,
		const int& p_HeightLowerLimit = 0,
		const int& p_HeightUpperLimit = BackGroundScale.first - 200,
		const int& p_WidthLowerLimit = 150,
		const int& p_WidthUpperLimit = BackGroundScale.second - 200);									//构造函数

	~A_Enemy();																							//析构函数

	 bool Segmentation(cv::Mat& segBackGround) override;												//将当前对象拷贝到segBackGround

	 void EnemyAutoMovie();																				//敌人自动移动

	 bool DestoryObj() override;																		//自我销毁函数（对象碰撞游戏边界时发生）

	 void EnemyFire();																					//敌人开火

	 bool EnemyBulletMove();																			//敌人子弹移动

	/*--- Get ---*/
	 std::vector<A_EnemyBullets> GetBulletObj();														//获取子弹信息

	/*--- Set ---*/
	 void SetBulletObj(std::vector<A_EnemyBullets> para);												//设置子弹信息

	/*--- 碰撞检测系列 ---*/
	 bool CollionEnemyBulletWithPlayer(A_PlayerFighter Target);											//检测：玩家 碰 敌人子弹

};

