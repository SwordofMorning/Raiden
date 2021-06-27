#include "G_GameScene.h"

G_GameScene::G_GameScene(const std::string& p_GameBackGround_Path,
	const int& p_NumberofEnemy,
	const std::string& p_BossImgPath, 
	const int& p_BossHealth)
{
	m_ImgGameBackScene = cv::imread(p_GameBackGround_Path, 1);
	m_ImgGameBackScene.copyTo(m_ImgGameBackSceneClone);
	m_NumberofEnemy = p_NumberofEnemy;
	m_Boss = A_Boss(p_BossImgPath, p_BossHealth);
}
