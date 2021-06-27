#pragma once
#include "A_Actor.h"
#include "A_Enemy.h"
#include <random>

//EnemyHit:16 * 16
extern const std::pair<int, int> EnemyHitSacle;

class A_EnemyBullets : public A_Actor
{
private:

	/*--- �ڵ��ƶ����� ---*/
	int m_BulletMoveSpeed;																			//�ڵ��ƶ��Ĳ���

	/*--- �ڵ����������ս�������˹��ܣ� ---*/
	double m_BulletMoveTargetAngle_Sin;																//�ڵ��ƶ��ķ���sin Ĭ��90�� �� 1
	double m_BulletMoveTargetAngle_Cos;																//�ڵ��ƶ��ķ���cos Ĭ��90�� �� 0

public:
	A_EnemyBullets(std::string p_path = ".\\Source\\Re_EnemyBullets\\EnemyHit.png",
		const int& p_height = 350, const int& p_width = 350,
		const int& p_HeightLowerLimit = 32,
		const int& p_HeightUpperLimit = BackGroundScale.first - 50,
		const int& p_WidthLowerLimit = 32,
		const int& p_WidthUpperLimit = BackGroundScale.second - 32,
		const int& p_BulletMoveSpeed = 15,
		const double& p_BulletMoveTargetAngle_Sin = 1,
		const double& p_BulletMoveTargetAngle_Cos = 0);												//���캯��

	~A_EnemyBullets();																				//��������

	bool Segmentation(cv::Mat& segBackGround)override;												//����ǰ���󿽱���segBackGround

	//bool DestoryObj() override;																	//����Override

	bool operator==(A_EnemyBullets Target);															//op==����

	/*--- Get��Ա���� ---*/
	int GetBulletMoveSpeed();																		//����m_BulletMoveSpeed

};

