#pragma once

#include <utility>
#include "A_Actor.h"

extern const std::vector<std::pair<int, int>> BulletScale;

/*
BulletLevel_0��32 * 160
BulletLevel_1��64 * 160
BulletLevel_2��96 * 160
BulletLevel_3��128 * 160
*/

/*=== ���ս���ڵ��� ===*/
class A_Bullet :public A_Actor
{
private:

	/*--- �ڵ��ƶ����� ---*/
	int m_BulletMoveSpeed;																			//�ڵ��ƶ��Ĳ���

	/*--- �ڵ����������ս�������˹��ܣ� ---*/
	double m_BulletMoveTargetAngle_Sin;																//�ڵ��ƶ��ķ���sin Ĭ��90�� �� 1
	double m_BulletMoveTargetAngle_Cos;																//�ڵ��ƶ��ķ���cos Ĭ��90�� �� 0

public:
	A_Bullet(std::string p_path = ".\\Source\\Re_Bullets\\BulletLevel_0.png",
		const int& p_height = 350, const int& p_width = 350,
		const int& p_HeightLowerLimit = 64,
		const int& p_HeightUpperLimit = BackGroundScale.first - 128,
		const int& p_WidthLowerLimit = 128,
		const int& p_WidthUpperLimit = BackGroundScale.second - 180,
		const int& p_BulletMoveSpeed = 80,
		const double& p_BulletMoveTargetAngle_Sin = 1,
		const double& p_BulletMoveTargetAngle_Cos = 0);												//���캯��

	~A_Bullet();																					//��������

	bool Segmentation(cv::Mat& segBackGround)override;												//����ǰ���󿽱���segBackGround

	bool DestoryObj() override;																		//�������ٺ�����������ײ��Ϸ�߽�ʱ������

	bool operator==(A_Bullet Target);																//op==����

	/*--- Get��Ա���� ---*/
	int GetBulletMoveSpeed();																		//����m_BulletMoveSpeed
};