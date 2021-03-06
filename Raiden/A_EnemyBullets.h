#pragma once
#include "A_Actor.h"
#include "A_Enemy.h"
#include <random>

//EnemyHit:16 * 16
extern const std::pair<int, int> EnemyHitSacle;

class A_EnemyBullets : public A_Actor
{
private:

	/*--- 炮弹移动参数 ---*/
	int m_BulletMoveSpeed;																			//炮弹移动的步长

	/*--- 炮弹锁定（玩家战机不含此功能） ---*/
	double m_BulletMoveTargetAngle_Sin;																//炮弹移动的方向sin 默认90° 即 1
	double m_BulletMoveTargetAngle_Cos;																//炮弹移动的方向cos 默认90° 即 0

public:
	A_EnemyBullets(std::string p_path = ".\\Source\\Re_EnemyBullets\\EnemyHit.png",
		const int& p_height = 350, const int& p_width = 350,
		const int& p_HeightLowerLimit = 32,
		const int& p_HeightUpperLimit = BackGroundScale.first - 50,
		const int& p_WidthLowerLimit = 32,
		const int& p_WidthUpperLimit = BackGroundScale.second - 32,
		const int& p_BulletMoveSpeed = 15,
		const double& p_BulletMoveTargetAngle_Sin = 1,
		const double& p_BulletMoveTargetAngle_Cos = 0);												//构造函数

	~A_EnemyBullets();																				//析构函数

	bool Segmentation(cv::Mat& segBackGround)override;												//将当前对象拷贝到segBackGround

	//bool DestoryObj() override;																	//无需Override

	bool operator==(A_EnemyBullets Target);															//op==重载

	/*--- Get成员函数 ---*/
	int GetBulletMoveSpeed();																		//返回m_BulletMoveSpeed

};

