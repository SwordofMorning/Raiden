#include "G_MainGame.h"

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;
extern const std::vector<std::pair<int, int>> BulletScale;
extern const std::pair<int, int> MouseMoveUpDownLimit;
extern const std::pair<int, int> MouseMoveLeftRightLimit;


/*--- ����¼����� ---*/
int MousePosX(350);							//����Ӧ����Ļλ��X
int MousePosY(350);							//����Ӧ����Ļλ��Y

bool MouseFire(false);

/*=== ��Ԫ���� ===*/

//����¼�����
void PlayerFighterMouseEvent(int p_event, int p_x, int p_y, int flag, void* ustc)
{
	MousePosX = p_x;
	MousePosY = p_y;

	MouseFire = false;
	if (p_event == cv::EVENT_LBUTTONDOWN)
	{
		MouseFire = true;
	}
}

/*
event:
EVENT_MOUSEMOVE 0            #����
EVENT_LBUTTONDOWN 1          #������
EVENT_RBUTTONDOWN 2          #�Ҽ����
EVENT_MBUTTONDOWN 3          #�м����
EVENT_LBUTTONUP 4            #����ſ�
EVENT_RBUTTONUP 5            #�Ҽ��ſ�
EVENT_MBUTTONUP 6            #�м��ſ�
EVENT_LBUTTONDBLCLK 7        #���˫��
EVENT_RBUTTONDBLCLK 8        #�Ҽ�˫��
EVENT_MBUTTONDBLCLK 9        #�м�˫��

flag:
EVENT_FLAG_LBUTTON 1       #���I��ҷ
EVENT_FLAG_RBUTTON 2       #���I��ҷ
EVENT_FLAG_MBUTTON 4       #���I��ҷ
EVENT_FLAG_CTRLKEY 8       #(8~15)��Ctrl�����¼�
EVENT_FLAG_SHIFTKEY 16     #(16~31)��Shift�����¼�
EVENT_FLAG_ALTKEY 32       #(32~39)��Alt�����¼�

*/

//���캯��
G_MainGame::G_MainGame(const std::string& p_GameMainMenu_Path, 
	const std::string& p_GameEndMenu_Path, 
	const std::string& p_GameContinueMenu_Path, 
	const std::string& p_GameBackGround_Path1, 
	const std::string& p_GameBackGround_Path2, 
	const std::string& p_GameBackGround_Path3, 
	const std::string& p_GameBackGround_Path4,
	const std::string& p_GameBackGround_Path5,
	const std::string& p_BossImgPath_1, 
	const std::string& p_BossImgPath_2, 
	const std::string& p_BossImgPath_3,
	const std::string& p_BossImgPath_4, 
	const std::string& p_BossImgPath_5)
{
	//���˵�ҳ��
	m_GameMainMenu = cv::imread(p_GameMainMenu_Path, 1);
	m_GameEndMenu = cv::imread(p_GameEndMenu_Path, 1);
	m_GameContinueMenu = cv::imread(p_GameContinueMenu_Path, 1);

	//��ҵ÷�
	m_score = 0;

	//�ؿ������ã�BossѪ����246
	G_GameScene TempScene_1(p_GameBackGround_Path1, 20, p_BossImgPath_1, 120);
	G_GameScene TempScene_2(p_GameBackGround_Path2, 20, p_BossImgPath_2, 120);
	G_GameScene TempScene_3(p_GameBackGround_Path3, 20, p_BossImgPath_3, 120);
	G_GameScene TempScene_4(p_GameBackGround_Path4, 20, p_BossImgPath_4, 120);
	G_GameScene TempScene_5(p_GameBackGround_Path5, 20, p_BossImgPath_5, 120);
	m_VecGameScenes.push_back(TempScene_1);
	m_VecGameScenes.push_back(TempScene_2);
	m_VecGameScenes.push_back(TempScene_3);
	m_VecGameScenes.push_back(TempScene_4);
	m_VecGameScenes.push_back(TempScene_5);

	//����ͼƬ
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_01.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_02.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_03.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_04.png");

	//��ұ���Ĭ�ϳ�ʼ��

	//��Ϸ����������ʼ��

	//�÷ֵȼ�Ĭ�ϳ�ʼ��

	//BossUI
	m_BossComing_1 = A_Actor(".\\Source\\Re_UI\\BossComing1.png", 200, 250);
	m_BossComing_2 = A_Actor(".\\Source\\Re_UI\\BossComing2.png", 200, 250);
	m_BossHealth = A_Actor(".\\Source\\Re_UI\\BoosHealth.png", 0, 268);

	m_BossHealthBegin = cv::Point(275, 16);
	m_BossHealthEnd = cv::Point(514, 16);
}


//ս���ƶ�
bool G_MainGame::PlayerFighterMove()
{
	cv::setMouseCallback("Raiden", PlayerFighterMouseEvent);
	//���ص�

	(MousePosX > MouseMoveLeftRightLimit.second) ? MousePosX = MouseMoveLeftRightLimit.second : MousePosX;
	//���λ��X > �����ֵ
	(MousePosX < MouseMoveLeftRightLimit.first) ? MousePosX = MouseMoveLeftRightLimit.first : MousePosX;
	//���λ��X < ����Сֵ
	(MousePosY > MouseMoveUpDownLimit.second) ? MousePosY = MouseMoveUpDownLimit.second : MousePosY;
	//���λ��Y > �����ֵ
	(MousePosY < MouseMoveUpDownLimit.first) ? MousePosY = MouseMoveUpDownLimit.first : MousePosY;
	//���λ��Y < ����Сֵ

	int MoveParaX = MousePosX - m_PlayerFighter.GetPos().second;
	int MoveParaY = MousePosY - m_PlayerFighter.GetPos().first;
	//����ƶ����������λ�� - ս��λ��

	MoveParaX -= PlayerFighterScale.second / 2;
	MoveParaY -= PlayerFighterScale.first / 2;
	//��ȥ�ߴ磬��ս�������Ϊ������ʾ

	m_PlayerFighter.MovePos(MoveParaY, MoveParaX);
	//�ƶ�

	return true;
}

//���ս������
bool G_MainGame::PlayerFighterFire()
{
	cv::setMouseCallback("Raiden", PlayerFighterMouseEvent);

	if (MouseFire)
	{
		this->m_PlayerFighter.PlayerFighterFire_LeftClick();
	}
	return true;
}

//��Ϸѭ��
void G_MainGame::GameLoop()
{
	//����ִ����Ϸ��ʼ�˵�
	this->GameStartMainMenu();

	//��һ��
	this->GameScene(0);
	this->GameContinueMenu();

	//�ڶ���
	this->m_PlayerFighter.SetBulletLevel(1);
	this->GameScene(1);
	this->GameContinueMenu();

	//������
	this->m_PlayerFighter.SetBulletLevel(2);
	this->GameScene(2);
	this->GameContinueMenu();

	//���Ĺ�
	this->m_PlayerFighter.SetBulletLevel(3);
	this->GameScene(3);
	this->GameContinueMenu();

	//�����
	this->GameScene(4);
	this->GameEndMenu();
}

//��Ϸ�ؿ����������ؿ��� 0 - 4
void G_MainGame::GameScene(int p_SceneNum)
{
	//��������ѭ��ʹ��
	A_Enemy LoopEnemy_1(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, 200);
	A_Enemy LoopEnemy_2(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, 350);

	//����1��[200, 350]������2��[350. 600]

	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

	/*============================================= ��ͨ���� =============================================*/
	while (m_VecGameScenes[p_SceneNum].m_NumberofEnemy >= 0)
	{
		m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
		//��������

		this->UI_ScoreRank();
		//�÷�UI

		this->PlayerFighterMove();
		//����ƶ�
		this->PlayerFighterFire();
		//��ҿ���
		this->m_PlayerFighter.BulletMove();
		//����ӵ��ƶ�
		LoopEnemy_1.EnemyAutoMovie();
		LoopEnemy_2.EnemyAutoMovie();
		//�����ƶ�
		LoopEnemy_1.EnemyBulletMove();
		LoopEnemy_2.EnemyBulletMove();
		//�����ӵ��ƶ�

		//���1�ŵ�����ײ�ӵ�
		if (m_PlayerFighter.CollionEnemyWithBullet(LoopEnemy_1))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);

			/*--- ���˱�ը��Ч ---*/
			//����ʹ��Boom1��Boom2�����ʹ��Boom1��Boom3
			LoopEnemy_1.ActorBoom1();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			LoopEnemy_1.ActorBoom2();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			LoopEnemy_1.ActorBoom1();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
			/*--------------------*/

			m_VecGameScenes[p_SceneNum].m_NumberofEnemy--;
			//��������--

			m_score += 100;
			//�÷�++

			A_Enemy TempEnemy(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, RandomNum(200, 350));
			TempEnemy.SetBulletObj(LoopEnemy_1.GetBulletObj());
			LoopEnemy_1 = TempEnemy;
			//���˸�ԭ
		}

		//���2�ŵ�����ײ�ӵ�
		if (m_PlayerFighter.CollionEnemyWithBullet(LoopEnemy_2))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);

			/*--- ���˱�ը��Ч ---*/
			//����ʹ��Boom1��Boom2�����ʹ��Boom1��Boom3
			LoopEnemy_2.ActorBoom1();
			LoopEnemy_2.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			LoopEnemy_2.ActorBoom2();
			LoopEnemy_2.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			LoopEnemy_2.ActorBoom1();
			LoopEnemy_2.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
			/*--------------------*/

			m_VecGameScenes[p_SceneNum].m_NumberofEnemy--;
			//��������--

			m_score += 100;
			//�÷�++

			A_Enemy TempEnemy(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, RandomNum(350, 600));
			TempEnemy.SetBulletObj(LoopEnemy_2.GetBulletObj());
			LoopEnemy_2 = TempEnemy;
			//���˸�ԭ
		}

		//��ұ�����
		if (LoopEnemy_1.CollionEnemyBulletWithPlayer(this->m_PlayerFighter) || LoopEnemy_2.CollionEnemyBulletWithPlayer(this->m_PlayerFighter))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);
			this->m_PlayerFighter.ActorBoom1();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			LoopEnemy_2.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom3();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			LoopEnemy_2.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom1();
			LoopEnemy_1.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			LoopEnemy_2.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ImgRecover();
			m_score -= 20;
		}

		//����1�����½�
		if (LoopEnemy_1.DestoryObj())
		{
			A_Enemy TempEnemy(".\\Source\\Re_Enemy\\Enemy_02.png", 0, RandomNum(200, 350));
			LoopEnemy_1 = TempEnemy;
			//���˸�ԭ
		}

		//����2�����½�
		if (LoopEnemy_2.DestoryObj())
		{
			A_Enemy TempEnemy(".\\Source\\Re_Enemy\\Enemy_02.png", 0, RandomNum(350, 600));
			LoopEnemy_2 = TempEnemy;
			//���˸�ԭ
		}

		/*--- ��ʾ ---*/
		this->m_PlayerFighter.Segmentation(this->m_GameBackground);
		LoopEnemy_1.Segmentation(this->m_GameBackground);
		LoopEnemy_2.Segmentation(this->m_GameBackground);
		m_ScoreRank.Segmentation(this->m_GameBackground);

		cv::imshow("Raiden", this->m_GameBackground);
		cv::waitKey(30);
	}

	

	/*=============================================== Boss ===============================================*/
	//BossUI
	PlaySound(".\\Source\\Re_Sound\\BossComing.wav", NULL, SND_ASYNC);
	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
	m_BossComing_1.Segmentation(this->m_GameBackground);
	cv::imshow("Raiden", this->m_GameBackground);
	cv::waitKey(500);
	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
	m_BossComing_2.Segmentation(this->m_GameBackground);
	cv::imshow("Raiden", this->m_GameBackground);
	cv::waitKey(500);

	//Boss����
	A_Boss LoopBoss(m_VecGameScenes[p_SceneNum].m_Boss);
	while (LoopBoss.IsBossAlive())
	{
		m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
		//��������

		LoopBoss.ImgRecover();
		//Boss��ԭ

		this->UI_ScoreRank();
		//�÷�UI

		this->PlayerFighterMove();
		//����ƶ�
		this->PlayerFighterFire();
		//��ҿ���
		this->m_PlayerFighter.BulletMove();
		//����ӵ��ƶ�
		LoopBoss.AutoMove();
		//Boss�ƶ�
		LoopBoss.BossBulletMove();
		//Boss�ӵ��ƶ�

		//Boss�е�
		if (this->m_PlayerFighter.CollionBossWithBullet(LoopBoss))
		{
			LoopBoss.BossHealthReduce();

			LoopBoss.Hitted();
			//�ı�BOSS��ɫ
		}

		//����е�
		if (LoopBoss.CollionPlayerWithBossBullet(this->m_PlayerFighter))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);
			this->m_PlayerFighter.ActorBoom1();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//BossѪ��UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//BossѪ��
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom3();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//BossѪ��UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//BossѪ��
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom1();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//BossѪ��UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//BossѪ��
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ImgRecover();
			m_score -= 20;
		}

		/*--- ��ʾ ---*/

		m_BossHealth.Segmentation(this->m_GameBackground);
		//BossѪ��UI
		m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
		cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
		//BossѪ��


		this->m_PlayerFighter.Segmentation(this->m_GameBackground);
		LoopBoss.Segmentation(this->m_GameBackground);
		m_ScoreRank.Segmentation(this->m_GameBackground);

		cv::imshow("Raiden", this->m_GameBackground);
		cv::waitKey(30);
	}

	//����Boss
	PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);
	LoopBoss.ActorBoom1();
	LoopBoss.Segmentation(m_GameBackground);
	this->m_PlayerFighter.Segmentation(m_GameBackground);
	cv::imshow("Raiden", this->m_GameBackground);
	cv::waitKey(10);
	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

	LoopBoss.ActorBoom2();
	LoopBoss.Segmentation(m_GameBackground);
	this->m_PlayerFighter.Segmentation(m_GameBackground);
	cv::imshow("Raiden", this->m_GameBackground);
	cv::waitKey(10);
	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

	LoopBoss.ActorBoom1();
	LoopBoss.Segmentation(m_GameBackground);
	this->m_PlayerFighter.Segmentation(m_GameBackground);
	cv::imshow("Raiden", this->m_GameBackground);
	cv::waitKey(10);
	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);


}

//��Ϸ��ʼ�˵�
void G_MainGame::GameStartMainMenu()
{
	cv::namedWindow("Raiden", cv::WINDOW_AUTOSIZE);
	cv::imshow("Raiden", m_GameMainMenu);

	while (char key  = cv::waitKey(0))
	{
		if (key == 13)
		{
			break;
		}
	}
}

//�ؿ�������Ϸ����
void G_MainGame::GameContinueMenu()
{
	cv::imshow("Raiden", m_GameContinueMenu);

	while (char key = cv::waitKey(0))
	{
		if (key == 13)
		{
			break;
		}
	}
}

//��Ϸ����
void G_MainGame::GameEndMenu()
{
	cv::imshow("Raiden", m_GameEndMenu);
	cv::waitKey(0);
}

//�����
int G_MainGame::RandomNum(const int& LowerLimmit, const int& UpperLimmit)
{
	std::random_device rd;											    
	std::mt19937 gen(rd());											   
	std::uniform_int_distribution<> dis(LowerLimmit, UpperLimmit);	
	int num = dis(gen);
	return num;
}

//�÷ֺ���
void G_MainGame::UI_ScoreRank()
{
	if (m_score < 1000)										//D
	{
		this->m_ScoreRank.SetRankImg(0);
	}
	else if (m_score >= 1000 && m_score < 2000)				//C
	{
		this->m_ScoreRank.SetRankImg(1);
	}
	else if (m_score >= 2000 && m_score < 3000)				//B
	{
		this->m_ScoreRank.SetRankImg(2);
	}
	else if (m_score >= 3000 && m_score < 4000)				//A
	{
		this->m_ScoreRank.SetRankImg(3);
	}
	else if (m_score >= 4000 && m_score < 5000)				//S
	{
		this->m_ScoreRank.SetRankImg(4);
	}
	else if (m_score >= 5000 && m_score < 6000)				//SS
	{
		this->m_ScoreRank.SetRankImg(5);
	}
	else if (m_score >= 6000)								//SSS
	{
		this->m_ScoreRank.SetRankImg(6);
	}
}
