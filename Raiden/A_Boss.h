#pragma once

#include "A_Actor.h"
#include "A_EnemyBullets.h"
#include "A_PlayerFighter.h"

class A_PlayerFighter;
class A_EnemyBullets;

class A_Boss : public A_Actor
{
private:
	int m_health;																//BossѪ��

	std::vector<A_EnemyBullets> m_BulletObjList;								//���ڴ��ս�����ɵ��ڵ�

	bool m_MoveDir;																//�ƶ����� true��false��
	
	int m_MoveSpeed;															//�ƶ��ٶ�

	cv::Mat m_HitImg;															//�����е���Ƭ
public:
	A_Boss(std::string p_path = ".\\Source\\Re_Boss\\Boss_01.png",
		int p_health = 50, int p_MoveSpeed = 10,
		const int& p_height = 0, const int& p_width = 150,
		const int& p_HeightLowerLimit = 0,
		const int& p_HeightUpperLimit = BackGroundScale.first - 500,
		const int& p_WidthLowerLimit = 10,
		const int& p_WidthUpperLimit = BackGroundScale.second - 510);									//���캯��

	~A_Boss();																							//��������

	void AutoMove();																					//Boss�Զ��ƶ�

	void BossAutoFire();																				//Boss����

	bool Segmentation(cv::Mat& segBackGround) override;													//����ǰ���󿽱���segBackGround

	bool BossBulletMove();																				//Boss�ӵ��ƶ�

	void BossHealthReduce();																			//BossѪ������

	bool IsBossAlive();																					//Boss����ж�

	void Hitted();																						//Boss������

	 void ActorBoom1() override;																		//��ը��Ч

	 void ActorBoom2() override;																		//��ը��Ч

	 int GetHealth();																					//����Ѫ��

	/*--- ��ײ��� ---*/
	bool CollionPlayerWithBossBullet(A_PlayerFighter Target);											//��⣺��� �� Boss�ӵ�

};


