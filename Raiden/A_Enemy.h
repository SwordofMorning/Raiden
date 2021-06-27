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
	std::vector<A_EnemyBullets> m_BulletObjList;								//���ڴ��ս�����ɵ��ڵ�

	bool m_Alive;																//�жϵ����Ƿ��� => ����������ӵ�����ײ�����A_PlayerFighter�������
public:
	
	A_Enemy(std::string p_path = ".\\Source\\Re_Enemy\\Enemy_01.png",
		const int& p_height = 200, const int& p_width = 350,
		const int& p_HeightLowerLimit = 0,
		const int& p_HeightUpperLimit = BackGroundScale.first - 200,
		const int& p_WidthLowerLimit = 150,
		const int& p_WidthUpperLimit = BackGroundScale.second - 200);									//���캯��

	~A_Enemy();																							//��������

	 bool Segmentation(cv::Mat& segBackGround) override;												//����ǰ���󿽱���segBackGround

	 void EnemyAutoMovie();																				//�����Զ��ƶ�

	 bool DestoryObj() override;																		//�������ٺ�����������ײ��Ϸ�߽�ʱ������

	 void EnemyFire();																					//���˿���

	 bool EnemyBulletMove();																			//�����ӵ��ƶ�

	/*--- Get ---*/
	 std::vector<A_EnemyBullets> GetBulletObj();														//��ȡ�ӵ���Ϣ

	/*--- Set ---*/
	 void SetBulletObj(std::vector<A_EnemyBullets> para);												//�����ӵ���Ϣ

	/*--- ��ײ���ϵ�� ---*/
	 bool CollionEnemyBulletWithPlayer(A_PlayerFighter Target);											//��⣺��� �� �����ӵ�

};

