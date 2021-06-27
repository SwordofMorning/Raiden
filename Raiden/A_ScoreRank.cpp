#include "A_ScoreRank.h"

A_ScoreRank::A_ScoreRank(std::string p_path,
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit, 
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit):
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\D.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\C.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\B.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\A.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\S.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\SS.png");
	m_RankImgVec.push_back(".\\Source\\Re_ScoreRank\\SSS.png");
}

bool A_ScoreRank::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b Yellow{ 91, 132, 178 };

	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			Yellow == this->GetImg().at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			//以(first, second)为原点将this拷贝到seg
		}
	}
	re = true;

	return re;
}

//修正图片	
void A_ScoreRank::SetRankImg(int Rank)
{
	this->SetImg(cv::imread(m_RankImgVec[Rank], 1));
}
