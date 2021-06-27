#pragma once
#include <vector>
#include <string>
#include <opencv.hpp>
#include "A_Actor.h"


/*--- �÷���ʾ ---*/
class A_ScoreRank :public A_Actor
{
private:	
	std::vector<std::string> m_RankImgVec;				//���ͼ��·��
public:		
	A_ScoreRank(std::string p_path = ".\\Source\\Re_Enemy\\Enemy_01.png",
		const int& p_height = 0, const int& p_width = 0,
		const int& p_HeightLowerLimit = 0,
		const int& p_HeightUpperLimit = BackGroundScale.first - 200,
		const int& p_WidthLowerLimit = 150,
		const int& p_WidthUpperLimit = BackGroundScale.second - 200);								//���캯��

	bool Segmentation(cv::Mat& segBackGround) override;												//����ǰ���󿽱���segBackGround

	void SetRankImg(int Rank);																		//����ͼƬ	
};

