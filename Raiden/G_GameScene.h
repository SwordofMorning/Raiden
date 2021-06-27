#pragma once

#include <opencv.hpp>
#include <list>
#include "A_Enemy.h"
#include "A_Boss.h"

/*=== ��Ϸ�ؿ��� ===*/
class G_GameScene
{
public:
	/*--- ���� ---*/
	cv::Mat m_ImgGameBackScene;									//��Ϸ����ͼ
	cv::Mat m_ImgGameBackSceneClone;							//��Ϸ����ͼ����

	/*--- һ����� ---*/
	int m_NumberofEnemy;										//�������� => ����ֻ����۵ı仯		
	/*
	�����߼�����MinGame�з������ɣ�ֱ���ﵽ����������֮�����boss
	*/

	/*---Boss ---*/
	A_Boss m_Boss;												//�ؿ�Boss
public:
	G_GameScene(const std::string& p_GameBackGround_Path,
		const int& p_NumberofEnemy,
		const std::string& p_BossImgPath,
		const int& p_BossHealth );
};

