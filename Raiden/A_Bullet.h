#pragma once

#include <utility>
#include "A_Actor.h"

extern const std::vector<std::pair<int, int>> BulletScale;

/*
BulletLevel_0：32 * 160
BulletLevel_1：64 * 160
BulletLevel_2：96 * 160
BulletLevel_3：128 * 160
*/

/*=== 玩家战机炮弹类 ===*/
class A_Bullet :public A_Actor
{
private:

	/*--- 炮弹移动参数 ---*/
	int m_BulletMoveSpeed;																			//炮弹移动的步长

	/*--- 炮弹锁定（玩家战机不含此功能） ---*/
	double m_BulletMoveTargetAngle_Sin;																//炮弹移动的方向sin 默认90° 即 1
	double m_BulletMoveTargetAngle_Cos;																//炮弹移动的方向cos 默认90° 即 0

public:
	A_Bullet(std::string p_path = ".\\Source\\Re_Bullets\\BulletLevel_0.png",
		const int& p_height = 350, const int& p_width = 350,
		const int& p_HeightLowerLimit = 64,
		const int& p_HeightUpperLimit = BackGroundScale.first - 128,
		const int& p_WidthLowerLimit = 128,
		const int& p_WidthUpperLimit = BackGroundScale.second - 180,
		const int& p_BulletMoveSpeed = 80,
		const double& p_BulletMoveTargetAngle_Sin = 1,
		const double& p_BulletMoveTargetAngle_Cos = 0);												//构造函数

	~A_Bullet();																					//析构函数

	bool Segmentation(cv::Mat& segBackGround)override;												//将当前对象拷贝到segBackGround

	bool DestoryObj() override;																		//自我销毁函数（对象碰撞游戏边界时发生）

	bool operator==(A_Bullet Target);																//op==重载

	/*--- Get成员函数 ---*/
	int GetBulletMoveSpeed();																		//返回m_BulletMoveSpeed
};