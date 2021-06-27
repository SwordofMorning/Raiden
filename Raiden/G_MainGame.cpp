#include "G_MainGame.h"

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;
extern const std::vector<std::pair<int, int>> BulletScale;
extern const std::pair<int, int> MouseMoveUpDownLimit;
extern const std::pair<int, int> MouseMoveLeftRightLimit;


/*--- 鼠标事件变量 ---*/
int MousePosX(350);							//鼠标对应的屏幕位置X
int MousePosY(350);							//鼠标对应的屏幕位置Y

bool MouseFire(false);

/*=== 友元函数 ===*/

//鼠标事件函数
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
EVENT_MOUSEMOVE 0            #滑动
EVENT_LBUTTONDOWN 1          #左键点击
EVENT_RBUTTONDOWN 2          #右键点击
EVENT_MBUTTONDOWN 3          #中键点击
EVENT_LBUTTONUP 4            #左键放开
EVENT_RBUTTONUP 5            #右键放开
EVENT_MBUTTONUP 6            #中键放开
EVENT_LBUTTONDBLCLK 7        #左键双击
EVENT_RBUTTONDBLCLK 8        #右键双击
EVENT_MBUTTONDBLCLK 9        #中键双击

flag:
EVENT_FLAG_LBUTTON 1       #左鍵拖曳
EVENT_FLAG_RBUTTON 2       #右鍵拖曳
EVENT_FLAG_MBUTTON 4       #中鍵拖曳
EVENT_FLAG_CTRLKEY 8       #(8~15)按Ctrl不放事件
EVENT_FLAG_SHIFTKEY 16     #(16~31)按Shift不放事件
EVENT_FLAG_ALTKEY 32       #(32~39)按Alt不放事件

*/

//构造函数
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
	//主菜单页面
	m_GameMainMenu = cv::imread(p_GameMainMenu_Path, 1);
	m_GameEndMenu = cv::imread(p_GameEndMenu_Path, 1);
	m_GameContinueMenu = cv::imread(p_GameContinueMenu_Path, 1);

	//玩家得分
	m_score = 0;

	//关卡的设置：Boss血条宽246
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

	//敌人图片
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_01.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_02.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_03.png");
	m_VecEnemyImgPath.push_back(".\\Source\\Re_Enemy\\Enemy_04.png");

	//玩家保持默认初始化

	//游戏背景不做初始化

	//得分等级默认初始化

	//BossUI
	m_BossComing_1 = A_Actor(".\\Source\\Re_UI\\BossComing1.png", 200, 250);
	m_BossComing_2 = A_Actor(".\\Source\\Re_UI\\BossComing2.png", 200, 250);
	m_BossHealth = A_Actor(".\\Source\\Re_UI\\BoosHealth.png", 0, 268);

	m_BossHealthBegin = cv::Point(275, 16);
	m_BossHealthEnd = cv::Point(514, 16);
}


//战机移动
bool G_MainGame::PlayerFighterMove()
{
	cv::setMouseCallback("Raiden", PlayerFighterMouseEvent);
	//鼠标回调

	(MousePosX > MouseMoveLeftRightLimit.second) ? MousePosX = MouseMoveLeftRightLimit.second : MousePosX;
	//鼠标位置X > 右最大值
	(MousePosX < MouseMoveLeftRightLimit.first) ? MousePosX = MouseMoveLeftRightLimit.first : MousePosX;
	//鼠标位置X < 左最小值
	(MousePosY > MouseMoveUpDownLimit.second) ? MousePosY = MouseMoveUpDownLimit.second : MousePosY;
	//鼠标位置Y > 下最大值
	(MousePosY < MouseMoveUpDownLimit.first) ? MousePosY = MouseMoveUpDownLimit.first : MousePosY;
	//鼠标位置Y < 上最小值

	int MoveParaX = MousePosX - m_PlayerFighter.GetPos().second;
	int MoveParaY = MousePosY - m_PlayerFighter.GetPos().first;
	//相对移动参数：鼠标位置 - 战机位置

	MoveParaX -= PlayerFighterScale.second / 2;
	MoveParaY -= PlayerFighterScale.first / 2;
	//减去尺寸，让战机以鼠标为中心显示

	m_PlayerFighter.MovePos(MoveParaY, MoveParaX);
	//移动

	return true;
}

//玩家战机开火
bool G_MainGame::PlayerFighterFire()
{
	cv::setMouseCallback("Raiden", PlayerFighterMouseEvent);

	if (MouseFire)
	{
		this->m_PlayerFighter.PlayerFighterFire_LeftClick();
	}
	return true;
}

//游戏循环
void G_MainGame::GameLoop()
{
	//首先执行游戏开始菜单
	this->GameStartMainMenu();

	//第一关
	this->GameScene(0);
	this->GameContinueMenu();

	//第二关
	this->m_PlayerFighter.SetBulletLevel(1);
	this->GameScene(1);
	this->GameContinueMenu();

	//第三关
	this->m_PlayerFighter.SetBulletLevel(2);
	this->GameScene(2);
	this->GameContinueMenu();

	//第四关
	this->m_PlayerFighter.SetBulletLevel(3);
	this->GameScene(3);
	this->GameContinueMenu();

	//第五关
	this->GameScene(4);
	this->GameEndMenu();
}

//游戏关卡：参数：关卡数 0 - 4
void G_MainGame::GameScene(int p_SceneNum)
{
	//两个敌人循环使用
	A_Enemy LoopEnemy_1(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, 200);
	A_Enemy LoopEnemy_2(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, 350);

	//敌人1在[200, 350]，敌人2在[350. 600]

	m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

	/*============================================= 普通敌人 =============================================*/
	while (m_VecGameScenes[p_SceneNum].m_NumberofEnemy >= 0)
	{
		m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
		//场景覆盖

		this->UI_ScoreRank();
		//得分UI

		this->PlayerFighterMove();
		//玩家移动
		this->PlayerFighterFire();
		//玩家开火
		this->m_PlayerFighter.BulletMove();
		//玩家子弹移动
		LoopEnemy_1.EnemyAutoMovie();
		LoopEnemy_2.EnemyAutoMovie();
		//敌人移动
		LoopEnemy_1.EnemyBulletMove();
		LoopEnemy_2.EnemyBulletMove();
		//敌人子弹移动

		//检测1号敌人碰撞子弹
		if (m_PlayerFighter.CollionEnemyWithBullet(LoopEnemy_1))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);

			/*--- 敌人爆炸特效 ---*/
			//敌人使用Boom1和Boom2，玩家使用Boom1和Boom3
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
			//敌人数量--

			m_score += 100;
			//得分++

			A_Enemy TempEnemy(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, RandomNum(200, 350));
			TempEnemy.SetBulletObj(LoopEnemy_1.GetBulletObj());
			LoopEnemy_1 = TempEnemy;
			//敌人复原
		}

		//检测2号敌人碰撞子弹
		if (m_PlayerFighter.CollionEnemyWithBullet(LoopEnemy_2))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);

			/*--- 敌人爆炸特效 ---*/
			//敌人使用Boom1和Boom2，玩家使用Boom1和Boom3
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
			//敌人数量--

			m_score += 100;
			//得分++

			A_Enemy TempEnemy(m_VecEnemyImgPath.at(RandomNum(0, 3)), 0, RandomNum(350, 600));
			TempEnemy.SetBulletObj(LoopEnemy_2.GetBulletObj());
			LoopEnemy_2 = TempEnemy;
			//敌人复原
		}

		//玩家被击中
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

		//敌人1到达下界
		if (LoopEnemy_1.DestoryObj())
		{
			A_Enemy TempEnemy(".\\Source\\Re_Enemy\\Enemy_02.png", 0, RandomNum(200, 350));
			LoopEnemy_1 = TempEnemy;
			//敌人复原
		}

		//敌人2到达下界
		if (LoopEnemy_2.DestoryObj())
		{
			A_Enemy TempEnemy(".\\Source\\Re_Enemy\\Enemy_02.png", 0, RandomNum(350, 600));
			LoopEnemy_2 = TempEnemy;
			//敌人复原
		}

		/*--- 显示 ---*/
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

	//Boss出场
	A_Boss LoopBoss(m_VecGameScenes[p_SceneNum].m_Boss);
	while (LoopBoss.IsBossAlive())
	{
		m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);
		//场景覆盖

		LoopBoss.ImgRecover();
		//Boss复原

		this->UI_ScoreRank();
		//得分UI

		this->PlayerFighterMove();
		//玩家移动
		this->PlayerFighterFire();
		//玩家开火
		this->m_PlayerFighter.BulletMove();
		//玩家子弹移动
		LoopBoss.AutoMove();
		//Boss移动
		LoopBoss.BossBulletMove();
		//Boss子弹移动

		//Boss中弹
		if (this->m_PlayerFighter.CollionBossWithBullet(LoopBoss))
		{
			LoopBoss.BossHealthReduce();

			LoopBoss.Hitted();
			//改变BOSS颜色
		}

		//玩家中弹
		if (LoopBoss.CollionPlayerWithBossBullet(this->m_PlayerFighter))
		{
			PlaySound(".\\Source\\Re_Sound\\EnemyBoom.wav", NULL, SND_ASYNC);
			this->m_PlayerFighter.ActorBoom1();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//Boss血条UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//Boss血条
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom3();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//Boss血条UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//Boss血条
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ActorBoom1();
			LoopBoss.Segmentation(m_GameBackground);
			this->m_PlayerFighter.Segmentation(m_GameBackground);
			m_ScoreRank.Segmentation(this->m_GameBackground);
			m_BossHealth.Segmentation(this->m_GameBackground);
			//Boss血条UI
			m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
			cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
			//Boss血条
			cv::imshow("Raiden", this->m_GameBackground);
			cv::waitKey(10);
			m_VecGameScenes[p_SceneNum].m_ImgGameBackScene.copyTo(m_GameBackground);

			this->m_PlayerFighter.ImgRecover();
			m_score -= 20;
		}

		/*--- 显示 ---*/

		m_BossHealth.Segmentation(this->m_GameBackground);
		//Boss血条UI
		m_BossHealthEnd = cv::Point(LoopBoss.GetHealth() * 2 + 275, 16);
		cv::line(this->m_GameBackground, m_BossHealthBegin, m_BossHealthEnd, cv::Scalar(0, 0, 255), 15);
		//Boss血条


		this->m_PlayerFighter.Segmentation(this->m_GameBackground);
		LoopBoss.Segmentation(this->m_GameBackground);
		m_ScoreRank.Segmentation(this->m_GameBackground);

		cv::imshow("Raiden", this->m_GameBackground);
		cv::waitKey(30);
	}

	//击败Boss
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

//游戏开始菜单
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

//关卡结束游戏继续
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

//游戏结束
void G_MainGame::GameEndMenu()
{
	cv::imshow("Raiden", m_GameEndMenu);
	cv::waitKey(0);
}

//随机数
int G_MainGame::RandomNum(const int& LowerLimmit, const int& UpperLimmit)
{
	std::random_device rd;											    
	std::mt19937 gen(rd());											   
	std::uniform_int_distribution<> dis(LowerLimmit, UpperLimmit);	
	int num = dis(gen);
	return num;
}

//得分函数
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
