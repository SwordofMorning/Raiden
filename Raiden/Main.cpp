#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include <opencv.hpp>
#include <iostream>
#include <vector>
#include <utility>

/*
	��������800 * ��1000
	���ս���� 128 * 128
	�ڵ���bullet_girl_1_level_4.png 4�� 128 * 180
	��A_Actor.h

	�ӵ�ģ�ͣ�
	BulletLevel_0��32 * 160
	BulletLevel_1��64 * 160
	BulletLevel_2��96 * 160
	BulletLevel_3��128 * 160

	�����ӵ���16 * 16
*/

/*=== Extern �������� ===*/
//����
extern const std::pair<int, int> BackGroundScale = std::make_pair<int, int>(1000, 800);
//�ڵ�
extern const std::vector<std::pair<int, int>> BulletScale
{ 
	std::make_pair<int, int>(160, 32),
	std::make_pair<int, int>(160, 64),
	std::make_pair<int, int>(160, 96), 
	std::make_pair<int, int>(160, 128) 
};
//���ս��
extern const std::pair<int, int> PlayerFighterScale = std::make_pair<int, int>(128, 128);
//�����Ч����
extern const std::pair<int, int> MouseMoveUpDownLimit = std::make_pair<int, int>(156, 1000 - 156);
extern const std::pair<int, int> MouseMoveLeftRightLimit = std::make_pair<int, int>(156, 800 - 156);
//�����ӵ�
extern const std::pair<int, int> EnemyHitSacle = std::make_pair<int, int>(16, 16);

#include "A_Actor.h"
#include "A_Bullet.h"
#include "A_PlayerFighter.h"
#include "G_GameScene.h"
#include "G_MainGame.h"

int main(int argc, char** argv)
{	
	//������wav
	mciSendString(TEXT(("open \".\\Source\\Re_Sound\\BGM.mp3\" alias PlayerFire")), NULL, 0, NULL);
	mciSendString("play PlayerFire repeat", NULL, 0, NULL);


	G_MainGame MG;

	MG.GameLoop();
	


	return 0;
}