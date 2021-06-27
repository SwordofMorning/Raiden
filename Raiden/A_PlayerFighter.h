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

//�ӵ�����׼��
class BulletOrderOP;

/*=== ���ս���� ===*/
class A_PlayerFighter :public A_Actor
{
private:	
	/*--- �ɻ����� ---*/
	const int m_HealthAtBegin = 5;						//����5����
	int m_Health;										//��ǰѪ��

	/*--- �ɻ��ڵ� ---*/
	std::vector<std::string> m_BulletImgPath;			//�ڵ�ͼ�����飨�������ƣ�
	int m_BulletLevel;									//��ǰ�ڵ��ȼ�
	const int m_BulletLevelLowerLimit = 0;				//�ڵ��ȼ��½�
	const int m_BulletLevelUpperLimit = 3;				//�ڵ��ȼ��Ͻ�
	std::vector<A_Bullet> m_BulletObjList;				//���ڴ��ս�����ɵ��ڵ�

public:
	A_PlayerFighter(std::string p_path = ".\\Source\\Re_PlayerFighter\\PlayerFighter_01.png",
		const int& p_height = 500, const int& p_width = 350,
		const int& p_HeightLowerLimit = 20,
		const int& p_HeightUpperLimit = BackGroundScale.first - 20,
		const int& p_WidthLowerLimit = 20,
		const int& p_WidthUpperLimit = BackGroundScale.second - 20);								//���캯��

	~A_PlayerFighter();																				//��������

	A_PlayerFighter(const A_PlayerFighter& Target);													//���ƹ��캯��

	A_PlayerFighter operator=(const A_PlayerFighter& Target);										//opera= ����

	void PlayerFighterFire_LeftClick();																//���������

	bool Segmentation(cv::Mat& segBackGround) override;												//����ǰ���� �� �ӵ�������segBackGround

	bool BulletMove();																				//�ɻ������ӵ��ƶ�

	bool IsAlive();																					//�ж����Ѫ���Ƿ������Ϸ

	void SetBulletLevel(int p_level);																//�ӵ��ȼ�

	/*--- ��ײ���ϵ�� ---*/
	bool CollionFighterWithEnemy(A_Enemy Target);													//��⣺��� �� ����

	bool CollionEnemyWithBullet(A_Enemy Target);													//��⣺���� �� ����ӵ�

	bool CollionBossWithBullet(A_Boss Target);														//��⣺Boss �� ����ӵ�

};

class BulletOrderOP
{
public:
	bool operator()(A_Bullet A, A_Bullet B)
	{
		return A.GetPos().first < B.GetPos().first;
	}
};