#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include <opencv.hpp>
#include <iostream>
#include <vector>
#include <utility>

/*
	背景：宽800 * 高1000
	玩家战机： 128 * 128
	炮弹：bullet_girl_1_level_4.png 4级 128 * 180
	见A_Actor.h

	子弹模型：
	BulletLevel_0：32 * 160
	BulletLevel_1：64 * 160
	BulletLevel_2：96 * 160
	BulletLevel_3：128 * 160

	敌人子弹：16 * 16
*/

/*=== Extern 常量定义 ===*/
//背景
extern const std::pair<int, int> BackGroundScale = std::make_pair<int, int>(1000, 800);
//炮弹
extern const std::vector<std::pair<int, int>> BulletScale
{ 
	std::make_pair<int, int>(160, 32),
	std::make_pair<int, int>(160, 64),
	std::make_pair<int, int>(160, 96), 
	std::make_pair<int, int>(160, 128) 
};
//玩家战机
extern const std::pair<int, int> PlayerFighterScale = std::make_pair<int, int>(128, 128);
//鼠标有效界限
extern const std::pair<int, int> MouseMoveUpDownLimit = std::make_pair<int, int>(156, 1000 - 156);
extern const std::pair<int, int> MouseMoveLeftRightLimit = std::make_pair<int, int>(156, 800 - 156);
//敌人子弹
extern const std::pair<int, int> EnemyHitSacle = std::make_pair<int, int>(16, 16);

#include "A_Actor.h"
#include "A_Bullet.h"
#include "A_PlayerFighter.h"
#include "G_GameScene.h"
#include "G_MainGame.h"

int main(int argc, char** argv)
{	
	//不适于wav
	mciSendString(TEXT(("open \".\\Source\\Re_Sound\\BGM.mp3\" alias PlayerFire")), NULL, 0, NULL);
	mciSendString("play PlayerFire repeat", NULL, 0, NULL);


	G_MainGame MG;

	MG.GameLoop();
	


	return 0;
}